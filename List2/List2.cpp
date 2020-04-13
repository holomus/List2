#include "List2.h"

int List2::push_back(void *elem, size_t elemSize)
{
	Node *node = new Node(&back_sentry, back_sentry.prev, elem, elemSize);
	node->prev->next = node;
	node->next->prev = node;
	return 0;
}

int List2::push_front(void * elem, size_t elemSize)
{
	Node *node = new Node(front_sentry.next, &front_sentry, elem, elemSize);
	node->prev->next = node;
	node->next->prev = node;
	return 0;
}

void List2::pop_back()
{
	NodeIterator iter(back_sentry.prev);
	remove(&iter);
}

void List2::pop_front()
{
	NodeIterator iter(front_sentry.next);
	remove(&iter);
}

void* List2::front(size_t &size)
{
	if (empty()) throw BoundaryError();
	NodeIterator front(front_sentry.next);
	return front.getElement(size);
}

void* List2::back(size_t &size)
{
	if (empty()) throw BoundaryError();
	NodeIterator back(back_sentry.prev);
	return back.getElement(size);
}

int List2::insert(Iterator *iter, void * elem, size_t elemSize)
{
	NodeIterator *iterator = dynamic_cast<NodeIterator*>(iter);
	Node *iter_node = iterator->getNode();
	Node *node = new Node(iter_node, iter_node->prev, elem, elemSize);
	iter_node->prev->next = node;
	iter_node->prev = node;
	iterator->setNode(node);
	return 0;
}


