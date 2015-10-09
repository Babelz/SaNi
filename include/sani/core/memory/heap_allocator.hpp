#pragma once

#include "sani/types.hpp"
#include <vector>
#include <list>

namespace sani {

	enum AllocationPolicy {
		// Always keep the efficiency in mind when allocation
		// at the cost of speed.
		Efficiency,
		
		// Always keep the time in mind when allocating
		// at the cost of efficiency.
		LinearTimeAllocations,

		// Causes the allocator to use twice as much 
		// memory as it should but reduces allocation
		// times to constant.
		ConstantTimeAllocation
	};

	class Allocator {
	private:
		char* memory;
	public:
	};

	/// @class HeapAllocator heap_allocator.hpp "sani/core/memory/heap_allocator.hpp"
	/// @author voidbab
	///
	/// Basic heap allocator with defragmentation support.
	class HeapAllocator {
	private:
		Allocator allocator;
	public:
		HeapAllocator(const uint64 bytes);

		~HeapAllocator();

		HeapAllocator& operator =(HeapAllocator& other) = delete;
		HeapAllocator& operator =(HeapAllocator&& other) = delete;

		HeapAllocator(HeapAllocator& other) = delete;
		HeapAllocator(HeapAllocator&& other) = delete;
	};
}