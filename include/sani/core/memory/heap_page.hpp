#pragma once

#include "sani/core/memory/heap_block.hpp"
#include "sani/types.hpp"

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

		std::priority_queue<HeapBlock> releasedBlocks;
		std::list<HeapBlock> blocks;

		uint32 pagepointer;
	public:
		HeapPage(const uint32 size) : size(size),
									  pagepointer(0) {
			memory = new char[size];
		}

		inline bool canAllocate(const size_t size) {
			return pagepointer + size <= this->size || releasedBlocks.size() > 0;
		}

		template<class T> 
		inline T* allocate() {
			const size_t size = sizeof(T);

			if (pagepointer + size > this->size) {
				if (releasedBlocks.size() == 0) return nullptr;

				HeapBlock& releasedBlock = releasedBlocks.top();

				// Check if we can allocate from released blocks.
				if (releasedBlock.getSize() <= size) releasedBlocks.pop();
				else			        			return nullptr;

				// Allocate.
				const uint32 diff = releasedBlock.getSize() - size;

				if (diff > 0) {
					// Insert new block.
					/*
					HeapBlock block(releasedBlock.getHandle() + diff, diff);
					
					blocks.insert(releasedBlock, block);
					releasedBlocks.push(block);
					
					releasedBlock.shrink(diff);*/
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
					releasedBlocks.push(block);

					return true;
				}
			}

			return false;
		}

		// TODO: implement defragmentation logic.

		~HeapPage() {
			delete[] memory;
		}

		HeapPage(HeapPage& other) = delete;

		HeapPage& operator =(HeapPage& other) = delete;
		HeapPage& operator =(HeapPage&& other) = delete;
	};
}