#pragma once

template <typename T>
class Vector
{
	int _size = 0;
	int _capacity = 0;

	T* _data = nullptr;

public:
	Vector() {
		_size = 1;
		_capacity = 1;

		_data = new T[1];
	}
	~Vector() {//vector 해제는 여기서
		/*for (int i = 0; i < _capacity; i++) {
			delete _data[i];
		}*/
		delete[] _data;
	}

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
	void PushBack(T value) {
		//벡터가 꽉 참. => 1.2배 크기의 새 벡터로 옮기기
		if (_size == _capacity) {
			int newCapacity = static_cast<int>(_capacity * 1.2f);
			Reserve(newCapacity);
		}
		//데이터 집어넣기
		_data[_size] = value;
		_size++;
	}
	void PopBack() {
		if (_size == 0)
			return;
		_data[_size - 1] = NULL;
		_size--;
	}
	void Claer() {
		for (int i = 0; i < _size; i++) {
			_data[i] = NULL;
		}
		_size = 0;
	}

	const int& Size() { return _size; }
	const int& Capacity() { return _capacity; }

	T operator[](int index) {
		if (index <0 || index >= _size)
			return NULL;
		return _data[index];
	}
};

