#pragma once
#include "List2Abstract.h"
class List2 :
	public AbstractList2
{
public:
	List2(MemoryManager& mem) : AbstractList2(mem) 
	{
		front_sentry.next = &back_sentry;
		back_sentry.prev = &front_sentry;
	};
	int push_back(void *elem, size_t elemSize) override;
	int push_front(void *elem, size_t elemSize) override;
	void pop_back() override;
	void pop_front() override;
	void* front(size_t &size) override;
	void* back(size_t &size) override;
	int insert(Iterator *iter, void *elem, size_t elemSize) override;
	Iterator* find(void *elem, size_t size) override;
	Iterator* begin() override;
	Iterator* end() override;
	void remove(Iterator *iter) override;
	bool empty() override;
	void clear() override;
protected:
	struct DoubleNode : public Node {
		DoubleNode(Node *prev, Node *next, void *elem, size_t size) : Node(next, elem, size), prev(prev) {};
		DoubleNode() : Node(), prev(nullptr) {};
		Node* prev;
	};
	class DoubleNodeIterator : public NodeIterator {
	public:
		DoubleNodeIterator(Node *node) : NodeIterator(node) {};
		DoubleNodeIterator(DoubleNode *node) : NodeIterator(node) {};
		bool hasPrev() {
			return (static_cast<DoubleNode*>(node))->prev != nullptr;
		}
		void goToPrev() {
			if (!hasPrev()) throw ElementError();
			node = (static_cast<DoubleNode*>(node))->prev;
		}
		friend bool operator==(DoubleNodeIterator &left, DoubleNodeIterator &right) { return left.equals(&right); };
		friend bool operator!=(DoubleNodeIterator &left, DoubleNodeIterator &right) { return !left.equals(&right); };
	};
	DoubleNode back_sentry;
};

