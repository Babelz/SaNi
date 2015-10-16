#include "sani/core/memory/heap_allocator.hpp"

#define TWO_MEGABYTES 2097152 

namespace sani {
	
	HeapAllocator::HeapAllocator(const uint32 pageSize, const uint32 initialPages, const DefragmentationPolicy defragmentationPolicy) : pageSize(pageSize),
																																	    defragmentationPolicy(defragmentationPolicy)  {
		initialize(initialPages);
	}

	HeapAllocator::HeapAllocator(const uint32 initialPages, const DefragmentationPolicy defragmentationPolicy) : pageSize(TWO_MEGABYTES),
																												 defragmentationPolicy(defragmentationPolicy)  {
		initialize(initialPages);
	}

	HeapAllocator::HeapAllocator(const DefragmentationPolicy defragmentationPolicy) : pageSize(TWO_MEGABYTES),
																					  defragmentationPolicy(defragmentationPolicy) {
		initialize(1);
	}

	void HeapAllocator::initialize(const uint32 initialPages) {
		for (uint32 i = 0; i < initialPages; i++) pages.push_back(new HeapPage(pageSize));
	}

	float32 HeapAllocator::getFragmentation() const {
		// Frag% = sum of page frag%
		float32 fragmentation = 0.0f;

		for (const HeapPage* page : pages) fragmentation += page->getFragmentation();

		return fragmentation;
	}
	bool HeapAllocator::shouldDefragment() const {
		for (const HeapPage* page : pages) if (page->shouldDefragment()) return true;

		return false;
 	}
	void HeapAllocator::defragment() {
		for (HeapPage* page : pages) page->defragment();
	}
	bool HeapAllocator::fragmented() const {
		for (HeapPage* page : pages) if (page->fragmented()) return true;

		return false;
	}

	HeapAllocator::~HeapAllocator() {
		for (HeapPage* page : pages) delete page;
	}
}