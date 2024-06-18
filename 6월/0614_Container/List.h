#pragma once

template <typename T>
struct Node {
	Node<T>* next = nullptr;
	T data = NULL;
	Node<T>* prev = nullptr;

	Node(){}
	Node(const T& data) { this->data = data; }
};

template <typename T>
class List
{
	int _size;
	Node<T>* _head;

public:
	List() :
		_size(0)
	{
		_head = new Node<T>();
		_head->next = _head;
		_head->prev = _head;
	}

	class Iterator {
		Node<T>* nodePtr;
	public:
		Iterator() : nodePtr(nullptr) {}
		Iterator(Node<T>* otherPtr) : nodePtr(otherPtr) {}
		//Iterator 만들기에 필요한 것들
		//복사대입생성자
		Iterator(const Iterator& other) { nodePtr = other.nodePtr; }
		//복사대입연산자
		Iterator& operator=(const Iterator& other) { nodePtr = other.nodePtr; return *this; }
		//!= 비교연산자
		bool operator !=(const Iterator& other) { return nodePtr != other.nodePtr; }
		bool operator ==(const Iterator& other) { return nodePtr == other.nodePtr; }
		//++ 증감연산자
		Iterator& operator++() {
			nodePtr = nodePtr->next;

			return *this;
		}
		Iterator operator++(int) {
			Iterator result = *this;

			nodePtr = nodePtr->next;

			return result;
		}
		//* 간접연산자
		T& operator*() {
			return (*nodePtr).data;
		}
	};

	void PushBack(const T& val) {
		Node<T>* newNode = new Node<T>(val);
		Node<T>* next = _head;
		Node<T>* prev = _head->prev;

		newNode->next = next;
		next->prev = newNode;

		newNode->prev = prev;
		prev->next = newNode;

		_size++;
	}

	void PushFront(const T& val) {
		Node<T>* newNode = new Node<T>(val);
		Node<T>* next = _head->next;
		Node<T>* prev = _head;

		newNode->next = next;
		next->prev = newNode;

		newNode->prev = prev;
		prev->next = newNode;

		_size++;
	}

	Node<T>* FindNode(int index) {
		Node<T>* finding = _head->next;

		for (int i = 0; i < index; i++) {
			if (finding->next == _head) break;
			finding = finding->next;
		}

		return finding;
	}

	const T& operator[](unsigned int index) {
		return FindNode(index)->data;
	}

	void Insert(const T& value, Node<T>* prev) {
		Node<T>* newNode = new Node<T>(value);

		Node<T>* next = prev->next;

		newNode->next = next;
		next->prev = newNode;

		newNode->prev = prev;
		prev->next = newNode;

		_size ++;
	}

	void PopBack() {
		if (_size == 0) return;

		Node<T>* taget = _head->prev;

		Node<T>* prev = taget->prev;
		
		prev->next = _head;
		_head->prev = prev;

		delete taget;

		_size--;
	}
	void PopFront() {
		if (_size == 0) return;

		Node<T>* taget = _head->next;

		Node<T>* next = taget->next;

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

	List<T>::Iterator begin() { return List<T>::Iterator(_head->next); }
	List<T>::Iterator end() { return List<T>::Iterator(_head); }
};

