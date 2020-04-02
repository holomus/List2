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
	if (!hasNext()) throw NextElementError();
	node = node->next;
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


void* ListContainer::newNode(size_t sz)
{
	return _memory.allocMem(sz);
}

ListContainer::Iterator* ListContainer::newIterator()
{
	//is it what it is supposed to do
	//I dont understand
	return new NodeIterator;
}

int ListContainer::size() {
	return elem_count;
}

size_t ListContainer::max_bytes()
{
	return _memory.maxBytes();
}


ListContainer::Iterator* ListContainer::find(void *elem, size_t size)
{
	NodeIterator *iterator = nullptr;
	Node node(elem, size);
	for(NodeIterator iter(front_sentry.next); iter.hasNext(); iter.goToNext())
		if (iter.hasEqual(node))
		{
			iterator = new NodeIterator(iter);
			break;
		}
	return iterator;
}

//returns iterator to the position after last element
ListContainer::Iterator* ListContainer::end() {
	return (empty()) ? nullptr : new NodeIterator(&back_sentry);
}


//returns iterator to the first element
ListContainer::Iterator* ListContainer::begin() {
	return (empty()) ? nullptr : new NodeIterator(front_sentry.next);
}

void ListContainer::remove(Iterator *iter)
{
	NodeIterator* iterator = dynamic_cast<NodeIterator*>(iter);
	if (iterator->getNode()->isSame(front_sentry) || iterator->getNode()->isSame(back_sentry))
		throw BoundaryError();
	Node* node = iterator->getNode();
	node->prev->next = node->next;
	node->next->prev = node->prev;
	iterator->setNode(node->next);
	delete node;
}

void ListContainer::clear()
{
	if (empty()) return;
	NodeIterator iter(front_sentry.next);
	while (!iter.getNode()->isSame(back_sentry))
		remove(&iter);
}


bool ListContainer::empty() {
	return front_sentry.next == &back_sentry;
}


