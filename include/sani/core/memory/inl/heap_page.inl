#include "sani/core/memory/heap_page.hpp"

namespace sani {

	float32 HeapPage::getFragmentation() const {
		return fragmentation;
	}

	bool HeapPage::canAllocate(const uint32 size) {
		return pagepointer + size <= this->size || releasedBlocks.size() > 0;
	}

	bool HeapPage::isInAddressSpace(const IntPtr address) {
		const IntPtr lowAddress = reinterpret_cast<IntPtr>(&memory[0]);
		const IntPtr highAddress = reinterpret_cast<IntPtr>(&memory[size - 1]);

		return address >= lowAddress && address <= highAddress;
	}
}