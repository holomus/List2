#pragma once
#include "List2Abstract.h"
class List2 :
	public AbstractList2
{
	List2(MemoryManager &mem) :AbstractList2(mem) {};
	int push_back(void *elem, size_t elemSize) override;
	int push_front(void *elem, size_t elemSize) override;
	void pop_back() override;
	void pop_front() override;
	void* front(size_t &size) override;
	void* back(size_t &size) override;
	int insert(Iterator *iter, void *elem, size_t elemSize) override;
};

