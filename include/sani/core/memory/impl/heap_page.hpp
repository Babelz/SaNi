#include "sani/core/memory/heap_page.hpp"
#include "sani/debug.hpp"

namespace sani {

	template<class T>
	T* HeapPage::allocate() {
		const auto size = sizeof(T);
		
		// Free memory has been used, check for blocks.
		if (pagepointer + size > this->size) {
			if (releasedBlocks.size() == 0) return nullptr;

			HeapBlock& releasedBlock = releasedBlocks.top();

			// Check if we can allocate from released blocks.
			if (size <= releasedBlock.getSize()) {
				releasedBlocks.pop();
			} else {
				missedBytes += size;

				fragmentation = missedBytes / static_cast<float32>(this->size);

				return nullptr;
			}

			// Allocate.
			const uint32 diff = releasedBlock.getSize() - size;
			releasedBlock.reserve();

			if (diff > 0) {
				// Create new block size of diff.
				HeapBlock block(releasedBlock.getHandle() + diff, diff);
				releasedBlock.shrink(diff);

				auto pos = std::find(blocks.begin(), blocks.end(), releasedBlock);
				std::advance(pos, 1);

				blocks.insert(pos, block);
				releasedBlocks.push(block);
			}

			bytesUsed += size;

			return reinterpret_cast<T*>(releasedBlock.getHandle());
		}
		else {
			// We have some free space left, allocate from there.
			char* handle = &memory[pagepointer];

			blocks.push_back(HeapBlock(handle, size));

			pagepointer += size;
			bytesUsed += size;

			return reinterpret_cast<T*>(handle);
		}
	}

	template<class T>
	bool HeapPage::deallocate(T* element) {
		SANI_ASSERT(element != nullptr);

		char* handle = reinterpret_cast<char*>(element);

		for (HeapBlock& block : blocks) {
			if (block.getHandle() == handle) {
				element->~T();

				releasedBlocks.push(block);

				block.release();

				// Reduce bytes used.
				const auto size = sizeof(element);
				bytesUsed -= size;

				return true;
			}
		}

		return false;
	}
}