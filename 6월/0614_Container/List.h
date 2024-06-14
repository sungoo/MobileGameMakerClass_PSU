#pragma once

struct Node {
	Node* next = nullptr;
	int data;
	Node* prev = nullptr;

	Node(){}
	Node(int data) { this->data = data; }
};

class List
{
	int _size;
	Node* _head;

public:
	List() :
		_size(0)
	{
		_head = new Node();
		_head->next = _head;
		_head->prev = _head;
	}

	void PushBack(int val) {
		Node* newNode = new Node(val);
		Node* next = _head;
		Node* prev = _head->prev;

		newNode->next = next;
		next->prev = newNode;

		newNode->prev = prev;
		prev->next = newNode;

		_size++;
	}

	void PushFront(int val) {
		Node* newNode = new Node(val);
		Node* next = _head->next;
		Node* prev = _head;

		newNode->next = next;
		next->prev = newNode;

		newNode->prev = prev;
		prev->next = newNode;

		_size++;
	}

	Node* FindNode(int index) {
		Node* finding = _head->next;

		for (int i = 0; i < index; i++) {
			if (finding->next == _head) break;
			finding = finding->next;
		}

		return finding;
	}

	int operator[](int index) {
		return FindNode(index)->data;
	}

	void Insert(int value, Node* prev) {
		Node* newNode = new Node(value);

		Node* next = prev->next;

		newNode->next = next;
		next->prev = newNode;

		newNode->prev = prev;
		prev->next = newNode;

		_size ++;
	}

	void PopBack() {
		if (_size == 0) return;

		Node* taget = _head->prev;

		Node* prev = taget->prev;
		
		prev->next = _head;
		_head->prev = prev;

		delete taget;

		_size--;
	}
	void PopFront() {
		if (_size == 0) return;

		Node* taget = _head->next;

		Node* next = taget->next;

		next->prev = _head;
		_head->next = next;

		delete taget;

		_size--;
	}

	void Clear() {
		for (int i = 0; i < _size-1; i++) {
			PopBack();
		}
	}

	int Size() { return _size; }
};

