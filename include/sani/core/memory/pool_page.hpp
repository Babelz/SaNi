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
		PoolPage(const int32 size);

		/// Returns true ig the given address is located
		/// in the pages address space.
		inline bool isInAddressSpace(const IntPtr address);
		/// Returns true if the page can be used for allocations.
		inline bool canAllocate() const;

		/// Attempts to allocate. If this page can't be used
		/// for allocations, a null pointer will be returned.
		inline T* allocate();
		/// Deallocates the given element and calls it's 
		/// destructor.
		inline bool deallocate(T* element);

		~PoolPage();

		PoolPage(PoolPage& other) = delete;
		PoolPage(PoolPage&& other) = delete;

		PoolPage& operator =(PoolPage& other) = delete;
		PoolPage& operator =(PoolPage&& other) = delete;
	};
}

#include "sani/core/memory/impl/pool_page.hpp"
#include "sani/core/memory/inl/pool_page.inl"