#pragma once
#include "Container.h"
class GroupContainer :	public Container
{
public:
	GroupContainer(MemoryManager &mem);
	~GroupContainer() {
		clear();
	};
	int size() override;
	virtual size_t max_bytes() override;
	Iterator* find(void *elem, size_t size) override;
	Iterator* begin() override;
	Iterator* end() override;
	void remove(Iterator *iter) override;
	void clear() override;
	bool empty() override;
	struct NextElementError : public Error
	{
		NextElementError() : Error("No next element found!") {};
	};
	struct BoundaryError : public Error
	{
		BoundaryError() : Error("Trying to access boundaries of list!") {};
	};
protected:
	Iterator* newIterator() override;

	struct Node
	{
		Node(Node *next, Node *prev, void *elem, size_t size) : next(next), prev(prev), elem(elem), elem_size(size) {};
		Node(void *elem, size_t size) : Node(nullptr, nullptr, elem, size) {};
		Node() :Node(nullptr, nullptr, nullptr, 0) {};
		~Node() {
			delete elem;
			elem = nullptr;
		}
		Node *next;
		Node *prev;
		void *elem;
		size_t elem_size;
		bool isEqual(Node &right) {
			return elem == right.elem && elem_size == right.elem_size;
		}
		bool isSame(Node &right) {
			return prev == right.prev && next == right.next;
		};
		static void* operator new(size_t sz);
		static void operator delete(void* ptr);
	};
	class NodeIterator : public GroupContainer::Iterator 
	{
	public:
		NodeIterator(Node *node) : node(node) {};
		NodeIterator() : NodeIterator(nullptr) {};
		void* getElement(size_t &size) override;
		bool hasNext() override;
		void goToNext() override;
		bool equals(Iterator *right) override;
		void setNode(Node *node) { this->node = node; };
		Node* getNode() { return node; };
		NodeIterator& operator++();
		NodeIterator operator++(int);
		bool hasEqual(Node &right);
	protected:
		friend bool operator==(NodeIterator &left, NodeIterator &right) { return left.equals(&right); };
		friend bool operator!=(NodeIterator &left, NodeIterator &right) { return !left.equals(&right); };
	private:
		Node *node;
	};
	Node front_sentry;
	Node back_sentry;
	int elem_count;
};

