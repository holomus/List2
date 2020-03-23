#pragma once
#include "List2Abstract.h"
class ListContainer :	public AbstractList2
{
public:
	ListContainer(MemoryManager &mem) : AbstractList2(mem) {};
	~ListContainer() {};
	int size() override;
	virtual size_t max_bytes() override;
	Iterator* find(void *elem, size_t size) override;
	Iterator* begin() override;
	Iterator* newIterator() override;
	Iterator* end() override;
	void remove(Iterator *iter) override;
	void clear() override;
	bool empty() override;
	struct NextElementError : public Error
	{
		NextElementError() : Error("No next element found!") {};
	};
protected:
	struct Node
	{
		Node *next;
		Node *prev;
		void *elem;
		size_t elem_size;
	};

	class NodeIterator : public ListContainer::Iterator 
	{
	public:
		void* getElement(size_t &size) override;
		bool hasNext() override;
		void goToNext() override;
		bool equals(Iterator *right) override;
	private:
		Node *node;
	};
};

