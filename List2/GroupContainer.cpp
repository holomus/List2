#include "GroupContainer.h"


void* GroupContainer::NodeIterator::getElement(size_t& size)
{
	size = node->elem_size;
	return node->elem;
}

bool GroupContainer::NodeIterator::hasNext()
{
	return node->next != nullptr;
}

void GroupContainer::NodeIterator::goToNext()
{
	if (!hasNext()) throw NextElementError();
	node = node->next;
}

bool GroupContainer::NodeIterator::equals(Iterator* right)
{
	NodeIterator* iterator = dynamic_cast<NodeIterator*>(right);
	return iterator != nullptr && node->isSame(*iterator->node);
}

bool GroupContainer::NodeIterator::hasEqual(Node &element)
{
	return node->isEqual(element);
}

GroupContainer::NodeIterator& GroupContainer::NodeIterator::operator++()
{
	goToNext();
	return *this;
}

GroupContainer::NodeIterator GroupContainer::NodeIterator::operator++(int)
{
	NodeIterator copy(*this);
	operator++();
	return copy;
}


void* GroupContainer::newNode(size_t sz)
{
	return _memory.allocMem(sz);
}

GroupContainer::Iterator* GroupContainer::newIterator()
{
	//is it what it is supposed to do
	//I dont understand
	return new NodeIterator;
}

int GroupContainer::size() {
	return elem_count;
}

size_t GroupContainer::max_bytes()
{
	return _memory.maxBytes();
}


GroupContainer::Iterator* GroupContainer::find(void *elem, size_t size)
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
GroupContainer::Iterator* GroupContainer::end() {
	return (empty()) ? nullptr : new NodeIterator(&back_sentry);
}


//returns iterator to the first element
GroupContainer::Iterator* GroupContainer::begin() {
	return (empty()) ? nullptr : new NodeIterator(front_sentry.next);
}

void GroupContainer::remove(Iterator *iter)
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

void GroupContainer::clear()
{
	if (empty()) return;
	NodeIterator iter(front_sentry.next);
	while (!iter.getNode()->isSame(back_sentry))
		remove(&iter);
}


bool GroupContainer::empty() {
	return front_sentry.next == &back_sentry;
}


