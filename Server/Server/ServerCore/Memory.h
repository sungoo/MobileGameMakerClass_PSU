#pragma once
#include "Allocator.h"

//가변 템플릿
template<typename T, typename... Args>
T* xnew(Args... args)
{
	T* memory = static_cast<T*>(BaseAllocator::Alloc(sizeof(T)));

	//생성자 호출
	new(memory)T(std::forward<Args>(args)...);

	return memory;
}

template<typename T>
void xdelete(T* obj)
{
	//소멸자 호출
	obj->~T();

	BaseAllocator::Release(obj);
}

