#include "GroupContainer.h"

static MemoryManager* mem_manager = nullptr;

GroupContainer::GroupContainer(MemoryManager & mem)	: Container(mem)
{
	if (mem_manager != nullptr && mem_manager != &mem) throw MemoryManagerError();
	front_sentry.next = &back_sentry;
	elem_count = 0;
	mem_manager = &mem;
};

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
	if (!hasNext()) throw ElementError();
	node = node->next;
}

bool GroupContainer::NodeIterator::equals(Iterator* right)
{
	NodeIterator* iterator = dynamic_cast<NodeIterator*>(right);
	return iterator != nullptr && iterator->node == node;
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


GroupContainer::Iterator* GroupContainer::begin() {
	return (empty()) ? nullptr : new NodeIterator(front_sentry.next);
}

GroupContainer::Iterator* GroupContainer::end() {
	return (empty()) ? nullptr : new NodeIterator(&back_sentry);
}



void GroupContainer::clear()
{
	if (empty()) return;
	NodeIterator iter(front_sentry.next);
	while (iter.hasNext()) {
		remove(&iter);
	}
}

//удаляет элемент после удаления итератор указывает на следующий элемент
void GroupContainer::remove(Iterator *iter)
{
	if (empty()) throw IteratorError();
	if (!iter->hasNext()) throw BoundaryError();
	NodeIterator prev(&front_sentry);
	NodeIterator curr(front_sentry.next);
	while (!curr.equals(iter)) {
		curr.goToNext();
		prev.goToNext();
	}
	prev.getNode()->next = curr.getNode()->next;
	delete curr.getNode();
	prev.goToNext();
	iter = &prev;
	--elem_count;
}

bool GroupContainer::empty() {
	return front_sentry.next == &back_sentry;
}


void * GroupContainer::Node::operator new(size_t sz)
{
	return mem_manager->allocMem(sz);
}

void GroupContainer::Node::operator delete(void * ptr)
{
	mem_manager->freeMem(ptr);
	ptr = nullptr;
}
