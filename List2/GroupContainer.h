#pragma once
#include "Container.h"
class GroupContainer :	public Container
{
public:
	GroupContainer(MemoryManager &mem);
	virtual ~GroupContainer() {
		clear();
	};
	int size() override;
	size_t max_bytes() override;
	Iterator* find(void *elem, size_t size) override;
	Iterator* begin() override;
	virtual Iterator* end() override;
	virtual void remove(Iterator *iter) override;
	void clear() override;
	virtual bool empty() override;
	struct NextElementError : public Error
	{
		NextElementError() : Error("No next element found!") {};
	};
	struct BoundaryError : public Error
	{
		BoundaryError() : Error("Trying to access boundaries of container!") {};
	};
	struct IteratorError : public Error {
		IteratorError() : Error("Illegal iterator, does iterator belong to this container?") {};
	};
	struct MemoryManagerError : public Error {
		MemoryManagerError() : Error("Trying to change memory manager!") {};
	};
protected:
	Iterator* newIterator() override;

	struct Node
	{
		Node(Node *next, void *elem, size_t size) : next(next), elem(elem), elem_size(size) {};
		Node(void *elem, size_t size) : Node(nullptr, elem, size) {};
		Node() : Node(nullptr, nullptr, 0) {};
		~Node() {
			delete elem;
			elem = nullptr;
		}
		Node *next;
		void *elem;
		size_t elem_size;
		bool isEqual(Node &right) {
			return elem_size == right.elem_size && memcmp(right.elem, elem, elem_size) == 0;
		}
		bool isSame(Node &right) {
			return this == &right;
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
	int elem_count;
};

