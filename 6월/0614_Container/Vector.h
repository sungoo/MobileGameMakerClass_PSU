#pragma once

template <typename T>
class Vector
{
	unsigned int _size = 0;
	unsigned int _capacity = 0;

	T* _data = nullptr;

public:
	Vector() {
	}
	~Vector() {//vector 해제는 여기서
		delete[] _data;
	}

	class Iterator {
		T* ptr;
	public:
		Iterator() : ptr(nullptr){}
		Iterator(T* otherPtr) : ptr(otherPtr){}
		//Iterator 만들기에 필요한 것들
		//복사대입생성자
		Iterator(const Iterator& other) { ptr = other.ptr; }
		//복사대입연산자
		Iterator& operator=(const Iterator& other) { ptr = other.ptr; return *this; }
		//!= 비교연산자
		bool operator != (const Iterator& other) { return ptr != other.ptr; }
		bool operator == (const Iterator& other) { return ptr == other.ptr; }
		//++ 증감연산자
		Iterator& operator++() {
			++ptr;

			return *this;
		}
		Iterator operator++(int) {
			Iterator result = *this;
			
			++(this->ptr);

			return result;
		}
		//* 간접연산자
		T& operator*() {
			return (*ptr);
		}
	};

	void Reserve(const int capacity = 10) {
		//원래 벡터의 크기보다 더 작은 capacity 요구시, 무시
		if (capacity < _capacity)
			return;
		//capacity 만큼 새 벡터 만들기
		T* newVector = new T[capacity];
		//기존 벡터에 있던 내용들 모두 새 벡터로 옮기기.
		for (int i = 0; i < _size; i++) {
			newVector[i] = _data[i];
		}
		//기존 벡터 지우기
		delete[] _data;
		//새 벡터를 가리키게 설정
		_data = newVector;
		
		_capacity = capacity;
	}
	void PushBack(const T& value) {
		//벡터가 꽉 참. => 1.2배 크기의 새 벡터로 옮기기
		if (_size == _capacity) {
			int newCapacity = static_cast<int>(_capacity * 1.5f);
			Reserve(newCapacity);
		}
		//데이터 집어넣기
		_data[_size] = value;
		_size++;
	}
	void PopBack() {
		if (_size == 0)
			return;
		_size--;
	}
	void Claer() {
		_size = 0;
	}

	const int& Size() { return _size; }
	const int& Capacity() { return _capacity; }

	T& operator[](int index) {
		if (index < 0 || index >= _size)
			return _data[0];
		return _data[index];
	}

	Vector<T>::Iterator begin() {
		return Vector<T>::Iterator(_data);
	}
	Vector<T>::Iterator end() {
		return Vector<T>::Iterator(_data + _size);
	}
};

