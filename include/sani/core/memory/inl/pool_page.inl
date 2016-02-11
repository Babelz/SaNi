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
		return allocate(1);
	}
	template <class T>
	T* PoolPage<T>::allocate(const uint32 length) {
		// TODO: can't allocate array from released handles yet,
		//		 but could we?...

		// Allocate many.
		if (length > 1) {
			// Allocate array if we can.
			const uint32 storageSize = sizeof(T) * length;

			if (poolpointer + storageSize < size) {
				T* elements = reinterpret_cast<T*>(&memory[poolpointer]);
				poolpointer += storageSize;

				return elements;
			}

			// Could not allocate!
			return nullptr;
		}

		// Allocate single.
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

		// nullptr if we could not allocate!
		return element;
	}

	template <class T>
	void PoolPage<T>::deallocate(T* element) {
		releasedHandles.push(reinterpret_cast<char*>(element));

		element->~T();
	}
	template <class T>
	void PoolPage<T>::deallocate(T* elements, const uint32 length) {
		for (uint32 i = 0; i < length; i++) {
			T* element = &elements[i];

			releasedHandles.push(reinterpret_cast<char*>(element));

			element->~T();
		}
	}
}