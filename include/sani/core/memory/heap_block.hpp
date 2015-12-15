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
		inline HeapBlock(char* handle, const uint32 size);

		inline void shrink(const uint32 bytes);
		inline void grow(const uint32 bytes);

		inline uint32 getSize() const;
		inline char* getHandle() const;

		inline bool isReleased() const;
		inline void release();
		inline void reserve();

		inline ~HeapBlock();

		inline bool operator == (const HeapBlock& other) const;

		inline bool operator < (const HeapBlock& other) const;
	};
}

#include "sani/core/memory/inl/heap_block.inl"