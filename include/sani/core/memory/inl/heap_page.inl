#include "sani/core/memory/heap_page.hpp"

namespace sani {

	float32 HeapPage::getFragmentation() const {
		return fragmentation;
	}

	bool HeapPage::canAllocate(const uint32 size) {
		return pagepointer + size <= this->size || releasedBlocks.size() > 0;
	}
}