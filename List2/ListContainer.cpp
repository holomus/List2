#include "ListContainer.h"



void* ListContainer::NodeIterator::getElement(size_t& size)
{
	size = node->elem_size;
	return node->elem;
}

bool ListContainer::NodeIterator::hasNext()
{
	return node->next != nullptr;
}

void ListContainer::NodeIterator::goToNext()
{
	if (hasNext()) {
		node = node->next;
	}
	else throw NextElementError();
}

bool ListContainer::NodeIterator::equals(Iterator* right)
{
	NodeIterator* iterator = dynamic_cast<NodeIterator*>(right);
	return iterator != nullptr && node->isSame(*iterator->node);
}

bool ListContainer::NodeIterator::hasEqual(Node &element)
{
	return node->isEqual(element);
}

ListContainer::NodeIterator& ListContainer::NodeIterator::operator++()
{
	goToNext();
	return *this;
}

ListContainer::NodeIterator ListContainer::NodeIterator::operator++(int)
{
	NodeIterator copy(*this);
	operator++();
	return copy;
}


ListContainer::Iterator* ListContainer::newIterator() 
{
	//is it what it is supposed to do
	//I dont understand
	return new NodeIterator;
}

int ListContainer::size() {

}

size_t ListContainer::max_bytes()
{
	return size_t();
}


ListContainer::Iterator* ListContainer::find(void *elem, size_t size)
{
	NodeIterator* iterator = nullptr;
	for (auto cur = static_cast<NodeIterator*>(begin()); *cur != *static_cast<NodeIterator*>(end()); ++(*cur)) {
		if (cur->hasEqual(Node(elem, size))) {

		}
	}
	return iterator;
}

//returns iterator to the position after last element
ListContainer::Iterator* ListContainer::end() {
	return (front_sentry == back_sentry) ? nullptr : new NodeIterator(&back_sentry);
}


//returns iterator to the first element
ListContainer::Iterator* ListContainer::begin() {
	return (front_sentry == back_sentry) ? nullptr : new NodeIterator(front_sentry.next);
}

void ListContainer::remove(Iterator * iter)
{
}

void ListContainer::clear()
{
}


bool ListContainer::empty() {
	return front_sentry == back_sentry;
}
