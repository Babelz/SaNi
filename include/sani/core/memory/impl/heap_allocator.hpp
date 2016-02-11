#include "sani/core/memory/heap_allocator.hpp"

namespace sani {

	template<class T>
	T* HeapAllocator::allocate() {
		return allocate<T>(1);
	}
	template<class T>
	T* HeapAllocator::allocate(const uint32 length) {
		const uint32 size = sizeof(T) * length;
		T* element = nullptr;

		// Can't allocate as the requested block is larger than the
		// page size.
		if (size > pageSize) return nullptr;

		for (HeapPage* page : pages) {
			if (!page->canAllocate(size)) continue;

			element = page->allocate<T>(length);

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

	template<class T>
	bool HeapAllocator::deallocate(T* element) {
		SANI_ASSERT(element != nullptr);

		for (HeapPage* page : pages) if (page->deallocate<T>(element)) return true;

		return false;
	}
	template<class T>
	bool HeapAllocator::deallocate(T* elements, const uint32 length) {
		SANI_ASSERT(elements != nullptr);

		/// Find the page this block is located at.
		const IntPtr firstHandle = reinterpret_cast<IntPtr>(elements[0]);
		HeapPage* elementsPage = nullptr;
		
		for (HeapPage* page : pages) {
			if (page->isInAddressSpace(firstHandle)) {
				elementsPage = page;

				break;
			}
		}
	}
}