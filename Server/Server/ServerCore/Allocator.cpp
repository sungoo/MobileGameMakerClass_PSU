#include "pch.h"
#include "Allocator.h"

void* BaseAllocator::Alloc(size_t size)
{
	void* ptr = std::malloc(size);
	return ptr;
}

void BaseAllocator::Release(void* ptr)
{
	std::free(ptr);
}
