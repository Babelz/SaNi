#pragma once

#include "sani/core/memory/pool_page.hpp"
#include "sani/debug.hpp"
#include <list>

namespace sani {

	/// @class PagePoolAllocator page_pool_allocator.hpp "sani/core/memory/page_pool_allocator.hpp"
	/// @author voidbab
	///
	/// A generic pool allocator.
	template<class T>
	class PagePoolAllocator {
	private:
		const uint32 pageSize;

		std::list<PoolPage<T>*> pages;

		void initialize(const uint32 initialPages);
	public:
		/// Creates new pool allocator with given page size and with 
		/// given count of initial pages.
		PagePoolAllocator(const int32 pageSize, const int32 initialPages);
		/// Creates new pool allocator with given 
		/// page size and with one initial page.
		PagePoolAllocator(const int32 pageSize);
		/// Creates new pool allocator with page size of 32 elements
		/// and with one initial pages.
		PagePoolAllocator();

		/// Returns true if the given element is in this
		/// allocators address space.
		bool isInAddressSpace(T* element) const;

		/// Allocates new element of type T.
		T* allocate();
		T* allocate(const uint32 length);

		/// Deallocates the given element.
		bool deallocate(T* element);
		bool deallocate(T* elements, const uint32 length);

		/// Returns the count of pages.
		int32 pagesCount() const;

		/// Returns the total amount of bytes used.
		uint64 getBytesUsed() const;
		/// Returns the current capacity of the allocator.
		uint64 getTotalBytes() const;

		~PagePoolAllocator();

		PagePoolAllocator(const PagePoolAllocator&) = delete;
		PagePoolAllocator(const PagePoolAllocator&&) = delete;

		void operator =(const PagePoolAllocator&) = delete;
		void operator =(const PagePoolAllocator&&) = delete;
	};
}

#include "sani/core/memory/impl/page_pool_allocator.hpp"