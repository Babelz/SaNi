#include "sani/core/memory/pool_page.hpp"
#include "sani/debug.hpp"

namespace sani {

	template <class T>
	bool PoolPage<T>::isInAddressSpace(const IntPtr address) {
		return address >= lowAddress && address <= highAddress;
	}
	template <class T>
	bool PoolPage<T>::canAllocate() const {
		return poolpointer < size || releasedElements.size() > 0;
	}

	template <class T>
	T* PoolPage<T>::allocate() {
		T* element = nullptr;

		if (!releasedElements.empty()) {
			element = releasedElements.top();
			releasedElements.pop();
		} else {
			if (poolpointer < size) {
				element = &memory[poolpointer];
				poolpointer++;
			}
		}

		SANI_ASSERT(element != nullptr);

		return element;
	}

	template <class T>
	bool PoolPage<T>::deallocate(T* element) {
		// No address space checks, do it in the allocator.
		// Just assume this element is located in this pages
		// address space.
		SANI_ASSERT(element != nullptr);

		releasedElements.push(element);
		element->~T();

		return true;
	}
}