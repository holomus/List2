#include "List2.h"

int List2::push_back(void *elem, size_t elemSize)
{
	DoubleNode *node = new DoubleNode(back_sentry.prev, &back_sentry, elem, elemSize);
	back_sentry.prev->next = node;
	back_sentry.prev = node;
	++elem_count;
	return 0;
}

int List2::push_front(void * elem, size_t elemSize)
{
	DoubleNode *node = new DoubleNode(&front_sentry, front_sentry.next, elem, elemSize);
	(static_cast<DoubleNode*>(front_sentry.next))->prev = node;
	front_sentry.next = node;
	++elem_count;
	return 0;
}

void List2::pop_back()
{
	if (empty()) throw ElementError();
	DoubleNodeIterator iter(back_sentry.prev);
	remove(&iter);
}

void List2::pop_front()
{
	if (empty()) throw ElementError();
	DoubleNodeIterator iter(front_sentry.next);
	remove(&iter);
}

void* List2::front(size_t &size)
{
	if (empty()) throw ElementError();
	DoubleNodeIterator front(front_sentry.next);
	return front.getElement(size);
}

void* List2::back(size_t &size)
{
	if (empty()) throw ElementError();
	DoubleNodeIterator back(back_sentry.prev);
	return back.getElement(size);
}

int List2::insert(Iterator *iter, void * elem, size_t elemSize)
{
	DoubleNodeIterator *iterator = dynamic_cast<DoubleNodeIterator*>(iter);
	DoubleNode *iter_node = static_cast<DoubleNode*>(iterator->getNode());
	DoubleNode *node = new DoubleNode(iter_node->prev, iter_node, elem, elemSize);
	iter_node->prev->next = node;
	iter_node->prev = node;
	iterator->setNode(node);
	++elem_count;
	return 0;
}

List2::Iterator* List2::find(void * elem, size_t size)
{
	DoubleNodeIterator *iterator = nullptr;
	Node node(elem, size);
	for (DoubleNodeIterator iter(front_sentry.next); iter.hasNext(); iter.goToNext())
		if (iter.hasEqual(node))
		{
			iterator = new DoubleNodeIterator(iter);
			break;
		}
	return iterator;
}

List2::Iterator* List2::begin()
{
	return (empty()) ? nullptr : new DoubleNodeIterator(front_sentry.next);
}

List2::Iterator* List2::end()
{
	return (empty()) ? nullptr : new DoubleNodeIterator(&back_sentry);
}


bool List2::empty()
{
	return front_sentry.next == &back_sentry;
}

void List2::clear()
{
	if (empty()) return;
	DoubleNodeIterator iter(front_sentry.next);
	while (iter.hasNext()) {
		remove(&iter);
	}
}


void List2::remove(Iterator* iter)
{
	if (empty()) throw IteratorError();
	if (!iter->hasNext()) throw BoundaryError();
	DoubleNodeIterator *iterator = dynamic_cast<DoubleNodeIterator*>(iter);
	DoubleNode *iter_node = static_cast<DoubleNode*>(iterator->getNode());
	iter_node->prev->next = iter_node->next;
	(static_cast<DoubleNode*>(iter_node->next))->prev = iter_node->prev;
	iterator->goToNext();
	delete iter_node;
	--elem_count;
}
