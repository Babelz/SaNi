#pragma once

#include "sani/types.hpp"
#include <vector>
#include <list>

namespace sani {

	/// @class HeapAllocator heap_allocator.hpp "sani/core/memory/heap_allocator.hpp"
	/// @author voidbab
	///
	/// Basic heap allocator with defragmentation support.
	class HeapAllocator {
	private:
		struct Chunk {
			uint32 size;
			char* handle;

			Chunk() : size(0),
					  handle(nullptr) {
			}

			~Chunk() {
			}
		};

		const int64 heapStart;
		int64		heapEnd;
		int64		size;

		// The heap pointer.
		uint64 hp;
		// Memory region of the allocator.
		char* memory;

		std::list<Chunk> occupiedChunks;
		std::list<Chunk> releasedChunks;

		// Used to for quick lookups to find the address of an element.
		std::vector<char*> transitions;

		void resize();
	public:
		HeapAllocator(const uint64 bytes);
		HeapAllocator();

		template<typename T> 
		T* allocate(...) {
			return nullptr;

			// new (val) T(...);
		}

		template<typename T>
		void deallocate(T* element) {
		}

		~HeapAllocator();

		HeapAllocator& operator =(HeapAllocator& other) = delete;
		HeapAllocator& operator =(HeapAllocator&& other) = delete;

		HeapAllocator(HeapAllocator& other) = delete;
		HeapAllocator(HeapAllocator&& other) = delete;
	};
}