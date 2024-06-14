#pragma once

template <typename T>
class Vector
{
	int _size = 0;
	int _capacity = 0;

	int* _data = nullptr;

public:
	Vector();
	~Vector();//vector 해제는 여기서

	void Reserve(int capacity);
	void PushBack(int value);
	void PopBack();
	void Claer();

	const int& Size() { return _size; }
	const int& Capacity() { return _capacity; }

	int operator[](int index);
};

