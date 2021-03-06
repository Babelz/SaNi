#include "sani/core/memory/heap_page.hpp"
#include "sani/debug.hpp"

namespace sani {

	template<class T>
	T* HeapPage::allocate() {
		return allocate<T>(1);
	}

	template<class T>
	inline T* HeapPage::allocate(const uint32 length) {
		const uint32 storageSize = sizeof(T) * length;
		char* handle = nullptr;

		// Free memory has been used, check for blocks.
		// (realloc)
		if (pagepointer + storageSize > this->size) {
			if (releasedBlocks.size() == 0) return nullptr;

			HeapBlock& releasedBlock = releasedBlocks.top();

			// Check if we can allocate from released blocks.
			if (storageSize <= releasedBlock.getSize()) {
				releasedBlocks.pop();
			} else {
				missedBytes += storageSize;

				fragmentation = missedBytes / static_cast<float32>(this->size);
				fragmentation = fragmentation > 1.0f ? 1.0f : fragmentation;

				return nullptr;
			}

			// Allocate.
			const uint32 diff = releasedBlock.getSize() - storageSize;
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

			bytesUsed += storageSize;

			handle = releasedBlock.getHandle();
		} else {
			// Heap pointer is pointing to some free space that we have left, allocate from there.
			// (alloc)
			handle = &memory[pagepointer];

			blocks.push_back(HeapBlock(handle, storageSize));

			pagepointer += storageSize;
			bytesUsed += storageSize;
		}

		// Align if needed and return.
		T* element = reinterpret_cast<T*>(handle);

		return element;
	}

	bool HeapPage::internalDeallocate(char* const handle) {
		for (HeapBlock& block : blocks) {
			if (block.getHandle() == handle) {
				releasedBlocks.push(block);

				block.release();

				// Reduce bytes used.
				bytesUsed -= block.getSize();

				return true;
			}
		}

		return false;
	}

	template<class T>
	bool HeapPage::deallocate(T* element) {
		char* const handle = reinterpret_cast<char* const>(element);

		if (internalDeallocate(handle)) {
			element->~T();

			return true;
		}

		return false;
	}

	template<class T>
	inline bool HeapPage::deallocate(T* elements, const uint32 length) {
		char* const firstHandle = reinterpret_cast<char* const>(&elements[0]);
		
		if (internalDeallocate(firstHandle)) {
			for (uint32 i = 0; i < length; i++) (&elements[i])->~T();

			return true;
		}

		return false;
	}
}