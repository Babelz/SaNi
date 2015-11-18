#pragma once

#include "sani/core/memory/heap_block.hpp"
#include "sani/types.hpp"
#include <algorithm>
#include <list>
#include <queue>

namespace sani {

	/*
		Allocate with pp till we hit the end.
		Then start to use the released blocks.
	*/
	
	/// @class HeapPage heap_page.hpp "sani/core/memory/heap_page.hpp"
	/// @author voidbab
	///
	/// Dynamically allocated chunk of memory that is used 
	/// by the heap.
	class HeapPage {
	private:
		const uint32 size;
		char* memory;

		// Bytes missed when we tried to allocate.
		uint32 missedBytes;
		// Fragmentation in percents.
		// missedBytes / size.
		float32 fragmentation;

		std::priority_queue<HeapBlock> releasedBlocks;
		std::list<HeapBlock> blocks;

		uint32 pagepointer;

		void joinBlocks(std::list<HeapBlock>& newBlocks, std::list<HeapBlock>& newReleasedBlocks);
		void generateNewReleasedQueue(std::list<HeapBlock>& newReleasedBlocks);
	public:
		HeapPage(const uint32 size) : size(size),
									  pagepointer(0),
									  missedBytes(0),
									  fragmentation(0.0f) {
			memory = new char[size];
		}

		inline float32 getFragmentation() const {
			return fragmentation;
		}

		inline bool canAllocate(const size_t size) {
			return pagepointer + size <= this->size || releasedBlocks.size() > 0;
		}

		template<class T> 
		inline T* allocate() {
			const size_t size = sizeof(T);

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

				return reinterpret_cast<T*>(releasedBlock.getHandle());
			} else {
				// We have some free space left, allocate from there.
				char* handle = &memory[pagepointer];

				blocks.push_back(HeapBlock(handle, size));

				pagepointer += size;

				return reinterpret_cast<T*>(handle);
			}
		}
		template<class T>
		inline bool deallocate(T* element) {
			char* handle = reinterpret_cast<char*>(element);

			for (HeapBlock& block : blocks) {
				if (block.getHandle() == handle) {
					element->~T();
					
					releasedBlocks.push(block);
					
					block.release();

					return true;
				}
			}

			return false;
		}

		bool shouldDefragment() const;
		bool fragmented() const;
		void defragment();

		~HeapPage() {
			delete[] memory;
		}

		HeapPage(HeapPage& other) = delete;

		HeapPage& operator =(HeapPage& other) = delete;
		HeapPage& operator =(HeapPage&& other) = delete;
	};
}