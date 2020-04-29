#include "List2.h"

int List2::push_back(void *elem, size_t elemSize)
{
	DoubleNode *node = new DoubleNode(back_sentry.prev, &back_sentry, elem, elemSize);
	back_sentry.prev->next = node;
	back_sentry.prev = node;
	return 0;
}

int List2::push_front(void * elem, size_t elemSize)
{
	DoubleNode *node = new DoubleNode(&front_sentry, front_sentry.next, elem, elemSize);
	(static_cast<DoubleNode*>(front_sentry.next))->prev = node;
	front_sentry.next = node;
	return 0;
}

void List2::pop_back()
{
	if (empty()) throw ElementError();
	NodeIterator iter(back_sentry.prev);
	remove(&iter);
}

void List2::pop_front()
{
	if (empty()) throw ElementError();
	NodeIterator iter(front_sentry.next);
	remove(&iter);
}

void* List2::front(size_t &size)
{
	if (empty()) throw ElementError();
	NodeIterator front(front_sentry.next);
	return front.getElement(size);
}

void* List2::back(size_t &size)
{
	if (empty()) throw ElementError();
	NodeIterator back(back_sentry.prev);
	return back.getElement(size);
}

int List2::insert(Iterator *iter, void * elem, size_t elemSize)
{
	NodeIterator *iterator = dynamic_cast<NodeIterator*>(iter);
	DoubleNode *iter_node = static_cast<DoubleNode*>(iterator->getNode());
	DoubleNode *node = new DoubleNode(iter_node->prev, iter_node, elem, elemSize);
	iter_node->prev->next = node;
	iter_node->prev = node;
	iterator->setNode(node);
	return 0;
}

List2::Iterator* List2::end()
{
	return (empty()) ? nullptr : new NodeIterator(&back_sentry);
}


bool List2::empty()
{
	return front_sentry.next == &back_sentry;
}


void List2::remove(Iterator* iter)
{
	if (empty()) throw IteratorError();
	NodeIterator *iterator = dynamic_cast<NodeIterator*>(iter);
	DoubleNode *iter_node = static_cast<DoubleNode*>(iterator->getNode());
	iter_node->prev->next = iter_node->next;
	(static_cast<DoubleNode*>(iter_node->next))->prev = iter_node->prev;
	iterator->goToNext();
	delete iter_node;
}
