#include "ListContainer.h"



void* ListContainer::NodeIterator::getElement(size_t & size)
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
		node->elem = node->next->elem;
		node->elem_size = node->next->elem_size;
		node->prev = node->next->prev; //next->prev == current
		node->next = node->next->next;
	}
	else throw NextElementError();
}

bool ListContainer::NodeIterator::equals(Iterator* right)
{
	NodeIterator* iterator = dynamic_cast<NodeIterator*>(right);
	return iterator != nullptr && node == iterator->node;
}


ListContainer::Iterator* ListContainer::newIterator() 
{
	//is it what it is supposed to do 
	//I dont understand
	return new NodeIterator;
}
