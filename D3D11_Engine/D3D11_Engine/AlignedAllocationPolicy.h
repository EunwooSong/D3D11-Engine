#pragma once

template<size_t Alignment>
class AlignedAllocationPolicy
{
public:
	static void* operator new(size_t size) {
		return _aligned_malloc(size, Alignment);
	}

	static void operator delete(void* memory) {
		_aligned_free(memory);
	}
};

