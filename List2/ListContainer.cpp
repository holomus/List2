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
	return list_size;
}

size_t ListContainer::max_bytes()
{
	//should somehow work with memory manager
	//currently dont know how
	return size_t();
}


ListContainer::Iterator* ListContainer::find(void *elem, size_t size)
{
	size_t elem_size;
	for (auto cur = begin(); cur != end(); cur->goToNext()) {
		if (elem == cur->getElement(elem_size)) {
			if (size == elem_size) {
				return cur;
			}
		}
	}
	return nullptr;
}

//returns iterator to the position after last element
ListContainer::Iterator* ListContainer::end() {	
	if (empty())
		return nullptr;
	iterator->setNode(&back_sentry);
	return iterator;
}


//returns iterator to the first element
ListContainer::Iterator* ListContainer::begin() {
	if(empty())
		return nullptr;
	iterator->setNode(front_sentry.next);
	return iterator;
}

void ListContainer::remove(Iterator *iter)
{
	//you should be very careful here
	if (iterator->equals(iter)) {

	}
	else {
		find(iter)
	}

}

void ListContainer::clear()
{
}


bool ListContainer::empty() {
	return front_sentry.next == nullptr;
}
