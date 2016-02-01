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

		uint64 bytesUsed;
		uint32 pagepointer;

		uint32 align(const uint32 size) const;

		void joinBlocks(std::list<HeapBlock>& newBlocks, std::list<HeapBlock>& newReleasedBlocks);
		void generateNewReleasedQueue(std::list<HeapBlock>& newReleasedBlocks);
	public:
		HeapPage(const uint32 size);

		inline float32 getFragmentation() const;

		inline bool canAllocate(const uint32 size);

		template<class T> 
		inline T* allocate();

		template<class T>
		inline bool deallocate(T* element);

		bool shouldDefragment() const;
		bool fragmented() const;
		void defragment();

		uint64 getBytesUsed() const;

		~HeapPage();

		HeapPage(HeapPage& other) = delete;
		HeapPage(HeapPage&& other) = delete;

		HeapPage& operator =(HeapPage& other) = delete;
		HeapPage& operator =(HeapPage&& other) = delete;
	};
}

#include "sani/core/memory/impl/heap_page.hpp"
#include "sani/core/memory/inl/heap_page.inl"