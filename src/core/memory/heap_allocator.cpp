#include "sani/core/memory/heap_allocator.hpp"
#include "sani/debug.hpp"

namespace sani {
	
	static const uint32 BLOCK_TWO_MEGABYTES = 2097152;

	HeapAllocator::HeapAllocator(const uint32 pageSize, const uint32 initialPages, const DefragmentationPolicy defragmentationPolicy) : pageSize(pageSize),
																																	    defragmentationPolicy(defragmentationPolicy)  {
		initialize(initialPages);
	}

	HeapAllocator::HeapAllocator(const uint32 initialPages, const DefragmentationPolicy defragmentationPolicy) : pageSize(BLOCK_TWO_MEGABYTES),
																												 defragmentationPolicy(defragmentationPolicy)  {
		initialize(initialPages);
	}

	HeapAllocator::HeapAllocator(const DefragmentationPolicy defragmentationPolicy) : pageSize(BLOCK_TWO_MEGABYTES),
																					  defragmentationPolicy(defragmentationPolicy) {
		initialize(1);
	}

	void HeapAllocator::initialize(const uint32 initialPages) {
		for (uint32 i = 0; i < initialPages; i++) pages.push_back(new HeapPage(pageSize));
	}

	uint32 HeapAllocator::pagesCount() const {
		return pages.size();
	}

	float32 HeapAllocator::getFragmentation() const {
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

	uint64 HeapAllocator::getBytesUsed() const {
		uint64 bytesUsed = 0;

		for (HeapPage* page : pages) bytesUsed += page->getBytesUsed();

		return bytesUsed;
	}
	uint64 HeapAllocator::getTotalBytes() const {
		return pageSize * pages.size();
	}
	uint64 HeapAllocator::getPageSize() const {
		return pageSize;
	}

	HeapAllocator::~HeapAllocator() {
		for (HeapPage* page : pages) delete page;
	}
}