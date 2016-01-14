#include "sani/core/memory/pool_page.hpp"
#include "sani/debug.hpp"

namespace sani {

	template <class T>
	bool PoolPage<T>::isInAddressSpace(const IntPtr address) {
		return address >= lowAddress && address <= highAddress;
	}
	template <class T>
	bool PoolPage<T>::canAllocate() const {
		return poolpointer < size || releasedHandles.size() > 0;
	}

	template <class T>
	T* PoolPage<T>::allocate() {
		T* element = nullptr;

		if (!releasedHandles.empty()) {
			element = reinterpret_cast<T*>(releasedHandles.top());
			releasedHandles.pop();
		} else {
			if (poolpointer < size) {
				element = reinterpret_cast<T*>(&memory[poolpointer]);
				poolpointer += sizeof(T);
			}
		}

		SANI_ASSERT(element != nullptr);

		return element;
	}

	template <class T>
	void PoolPage<T>::deallocate(T* element) {
		// No address space checks, do it in the allocator.
		// Just assume this element is located in this pages
		// address space.
		SANI_ASSERT(element != nullptr);

		// TODO: check if this works.
		// had to change the mem to char*... 
		releasedHandles.push(reinterpret_cast<char*>(element));
		element->~T();
	}
}