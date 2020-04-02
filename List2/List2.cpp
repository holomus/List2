#include "List2.h"

int List2::push_back(void *elem, size_t elemSize)
{
	Node *node = 
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


