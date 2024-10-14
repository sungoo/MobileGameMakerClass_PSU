#pragma once
class BaseAllocator
{
public:
	static void* Alloc(size_t size);
	static void  Release(void* ptr);
};

