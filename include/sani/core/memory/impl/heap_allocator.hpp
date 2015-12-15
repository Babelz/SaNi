#include "sani/core/memory/heap_allocator.hpp"

namespace sani {
	
	template<class T>
	T* HeapAllocator::allocate() {
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
			}
			else {
				return element;
			}
		}

		// If we still could not allocate, just 
		// create new page and allocate from there.
		HeapPage* page = new HeapPage(pageSize);
		pages.push_back(page);

		return page->allocate<T>();
	}

	template<class T>
	bool HeapAllocator::deallocate(T* element) {
		for (HeapPage* page : pages) if (page->deallocate<T>(element)) return true;

		return false;
	}
}