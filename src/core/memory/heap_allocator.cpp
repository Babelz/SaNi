#include "sani/core/memory/heap_allocator.hpp"

#define TWO_MEGABYTES 2097152 

namespace sani {
	
	HeapAllocator::HeapAllocator(const uint32 pageSize, const uint32 initialPages) : pageSize(pageSize) {
		initialize(initialPages);
	}

	HeapAllocator::HeapAllocator(const uint32 initialPages) : pageSize(TWO_MEGABYTES) {
		initialize(initialPages);
	}

	HeapAllocator::HeapAllocator() : pageSize(TWO_MEGABYTES) {
		initialize(1);
	}

	void HeapAllocator::initialize(const uint32 initialPages) {
		for (uint32 i = 0; i < initialPages; i++) pages.push_back(new HeapPage(pageSize));
	}

	HeapAllocator::~HeapAllocator() {
		for (HeapPage* page : pages) delete page;
	}
}