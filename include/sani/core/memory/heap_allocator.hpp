#pragma once

#include "sani/core/memory/defragmentation_policy.hpp"
#include "sani/core/memory/heap_page.hpp"
#include "sani/core/memory/memory.hpp"
#include "sani/contracts.hpp"
#include "sani/types.hpp"
#include "sani/debug.hpp"
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
		/// instead use the heaps deallocte method.
		/// Deallocate pools the memory and calls
		/// the destructor of the given object.
		template<class T>
		inline T* allocate() {
			const size_t size = sizeof(T);
			T* element = nullptr;

			for (HeapPage* page : pages) {
				if (!page->canAllocate(size)) continue;

				element = page->allocate<T>();

				if (element == nullptr) {
					// Could not allocate, see if we could defrag this
					// page and try to allocate again. Defrag, alloc. 
					// If we get the element allocated, just return it.
					if (defragmentationPolicy == DefragmentationPolicy::Automatic) {
						if (page->shouldDefragment()) page->defragment();

						element = page->allocate<T>();

						if (element != nullptr) return element;
					}
				} else {
					return element;
				}
			}

			// If we still could not allocate, just 
			// create new page and allocate from there.
			HeapPage* page = new HeapPage(pageSize);
			pages.push_back(page);

			return page->allocate<T>();
		}
		/// Releases the given object and calls it destructor.
		/// This object should not be used after this method has 
		/// been called.
		template<class T>
		inline bool deallocate(T* element) {
			for (HeapPage* page : pages) if (page->deallocate<T>(element)) return true;
			
			return false;
		}

		inline size_t pagesCount() const {
			return pages.size();
		}

		/// Returns fragmentation in percentage.
		float32 getFragmentation() const;
		/// Returns true if the heap should be defragmented.
		bool shouldDefragment() const;
		/// Defragments the heap.
		void defragment();
		/// Returns true if the heap contains fragmentation.
		bool fragmented() const;

		~HeapAllocator();

		HeapAllocator& operator =(HeapAllocator& other) = delete;
		HeapAllocator& operator =(HeapAllocator&& other) = delete;

		HeapAllocator(HeapAllocator& other) = delete;
		HeapAllocator(HeapAllocator&& other) = delete;
	};
}