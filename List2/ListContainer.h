#pragma once
#include "List2Abstract.h"
class ListContainer :	public AbstractList2
{
public:
	ListContainer(MemoryManager &mem) : AbstractList2(mem) {
		iterator = new NodeIterator(&front_sentry);
		list_size = 0;
		};                               
	~ListContainer() {
		clear();
		delete iterator;
		iterator = nullptr;
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
	struct WrongIteratorError : public Error {
		WrongIteratorError() : Error("That is not iterator for this type of container") {};
	};
protected:
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
	};
	
	class NodeIterator : public ListContainer::Iterator 
	{
	public:
		NodeIterator(Node *node) : node(node) {};
		NodeIterator() : NodeIterator(nullptr) {};
		~NodeIterator() {
			delete node;
			node = nullptr;
		}
		void* getElement(size_t &size) override;
		bool hasNext() override;
		void goToNext() override;
		bool equals(Iterator *right) override;

		bool hasEqual(Node &right);

		NodeIterator& operator++();
		NodeIterator operator++(int);
		friend bool operator==(NodeIterator &left, NodeIterator &right) { return left.equals(&right); };
		friend bool operator!=(NodeIterator &left, NodeIterator &right) { return !left.equals(&right); };
		void setNode(Node *node) { this->node = node; };
		Node* getNode() { return node; };
	private:
		friend ListContainer::ListContainer(MemoryManager &mem);
		Node *node;
	};
private:
	Node front_sentry;
	Node back_sentry;
	unsigned int list_size;
	NodeIterator *iterator;
	Iterator* newIterator() override;
};

