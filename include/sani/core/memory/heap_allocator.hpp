#pragma once

#include "sani/core/memory/defragmentation_policy.hpp"
#include "sani/core/memory/heap_page.hpp"
#include "sani/core/memory/memory.hpp"
#include "sani/types.hpp"
#include <list>

namespace sani {

	/// @class HeapAllocator heap_allocator.hpp "sani/core/memory/heap_allocator.hpp"
	/// @author voidbab
	///
	/// Basic heap allocator with defragmentation support.
	class HeapAllocator {
	private:
		const DefragmentationPolicy defragmentationPolicy;

		const uint32 pageSize;

		std::list<HeapPage*> pages;

		void initialize(const uint32 initialPages);
	public:
		/// Creates new heap allocator with given page size and 
		/// with given count of initial pages.
		HeapAllocator(const uint32 pageSize, const uint32 initialPages, const DefragmentationPolicy defragmentationPolicy);

		/// Creates new heap allocator with page size of 2mb (2097152-bytes)
		/// and with given count of initial pages.
		HeapAllocator(const uint32 initialPages, const DefragmentationPolicy defragmentationPolicy);

		/// Creates new heap allocator with page-size of 2mb (2097152-bytes)
		/// and with initial page count of one.
		HeapAllocator(const DefragmentationPolicy defragmentationPolicy);

		/// Allocates a new memory block of size of T.
		/// These blocks should never be deleted, but 
		/// instead use the heaps deallocate method.
		/// Deallocate pools the memory and calls
		/// the destructor of the given object.
		template<class T>
		inline T* allocate();

		/// Releases the given object and calls it destructor.
		/// This object should not be used after this method has 
		/// been called.
		template<class T>
		bool deallocate(T* element);

		uint32 pagesCount() const;

		/// Returns fragmentation in percentage.
		float32 getFragmentation() const;
		/// Returns true if the heap should be defragmented.
		bool shouldDefragment() const;
		/// Defragments the heap.
		void defragment();
		/// Returns true if the heap contains fragmentation.
		bool fragmented() const;

		/// Returns the total amount of bytes used.
		uint64 getBytesUsed() const;
		/// Returns the current capacity of the allocator.
		uint64 getTotalBytes() const;
		/// Returns the size of the page.
		uint64 getPageSize() const;

		~HeapAllocator();

		HeapAllocator& operator =(HeapAllocator& other) = delete;
		HeapAllocator& operator =(HeapAllocator&& other) = delete;

		HeapAllocator(HeapAllocator& other) = delete;
		HeapAllocator(HeapAllocator&& other) = delete;
	};
}

#include "sani/core/memory/impl/heap_allocator.hpp"