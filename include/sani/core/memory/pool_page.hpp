#pragma once

#include "sani/core/memory/memory.hpp"
#include "sani/types.hpp"
#include <stack>

namespace sani {

	template<class T>
	/// @class PoolPage pool_page.hpp "sani/core/memory/pool_page.hpp"
	/// @author voidbab
	///
	/// Represents a generic memory page used by the pool allocator.
	class PoolPage {
	private:
		IntPtr lowAddress;
		IntPtr highAddress;

		const int32 size;
		
		int32 poolpointer;

		std::stack<T*> releasedElements;
		T* memory;
	public:
		PoolPage(const int32 size) : size(size),
									 poolpointer(0) {
			memory = new T[size];

			lowAddress = reinterpret_cast<IntPtr>(&memory[0]);
			highAddress = reinterpret_cast<IntPtr>(&memory[size - 1]);
		}

		/// Returns true ig the given address is located
		/// in the pages address space.
		inline bool isInAddressSpace(const IntPtr address) {
			return address >= lowAddress && address <= highAddress;
		}
		/// Returns true if the page can be used for allocations.
		inline bool canAllocate() const {
			return poolpointer < size || releasedElements.size() > 0;
		}

		/// Attempts to allocate. If this page can't be used
		/// for allocations, a null pointer will be returned.
		inline T* allocate() {
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

			return element;
		}
		/// Deallocates the given element and calls it's 
		/// destructor.
		inline bool deallocate(T* element) {
			// No address space checks, do it in the allocator.
			// Just assume this element is located in this pages
			// address space.
			releasedElements.push(element);
			element->~T();

			return true;
		}

		~PoolPage() {
			delete[] memory;
		}
	};
}