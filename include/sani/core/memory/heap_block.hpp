#pragma once

#include "sani/types.hpp"

namespace sani {

	/// @class HeapBlock heap_block.hpp "sani/memory/heap_block.hpp"
	/// @author voidbab
	///
	/// Partition of the heap page memory.
	class HeapBlock {
	private:
		bool released;
		char* handle;
		uint32 size;
	public:
		HeapBlock(char* handle, const uint32 size) : handle(handle),
												     size(size),
													 released(false) {
		}

		inline void shrink(const uint32 bytes) {
			size -= bytes;
		}
		inline void grow(const uint32 bytes) {
			size += bytes;
		}

		inline uint32 getSize() const {
			return size;
		}
		inline char* getHandle() const {
			return handle;
		}

		inline bool isReleased() const {
			return released;
		}
		inline void release() {
			released = true;
		}
		inline void reserve() {
			released = false;
		}

		~HeapBlock() {
		}

		inline bool operator == (const HeapBlock& other) const {
			return handle == other.handle;
		}

		inline bool operator < (const HeapBlock& other) const {
			return size < other.size;
		}
	};
}