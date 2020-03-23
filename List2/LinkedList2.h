#pragma once
#include "List2Abstract.h"
class LinkedList2 :	public AbstractList2
{
public:
	LinkedList2(MemoryManager &mem) : AbstractList2(mem) {};
	~LinkedList2() {};
protected:
	class Node {
		Iterator *next;
		Iterator *prev;
		void *elem;
	};
};

