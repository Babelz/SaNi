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

		void initialize(const uint32 initialPages) {
			SANI_ASSERT(pageSize > 0);
			SANI_ASSERT(initialPages > 0);

			for (uint32 i = 0; i < initialPages; i++) pages.push_back(new PoolPage<T>(pageSize));
		}
	public:
		/// Creates new pool allocator with given page size and with 
		/// given count of initial pages.
		PagePoolAllocator(const int32 pageSize, const int32 initialPages) : pageSize(pageSize) {
			initialize(initialPages);
		}
		/// Creates new pool allocator with given 
		/// page size and with one initial page.
		PagePoolAllocator(const int32 pageSize) : pageSize(pageSize) {
			initialize(1);
		}
		/// Creates new pool allocator with page size of 32 elements
		/// and with one initial pages.
		PagePoolAllocator() : pageSize(32) {
			initialize(1);
		}

		/// Returns true if the given element is in this
		/// allocators address space.
		inline bool isInAddressSpace(T* element) const {
			const IntPtr address = reinterpret_cast<IntPtr>(element);

			for (const PoolPage<T>* page : pages) if (page->isInAddressSpace(address)) return true;

			return false;
		}

		/// Allocates new element of type T.
		inline T* allocate() {
			for (PoolPage<T>* page : pages) {
				if (page->canAllocate()) return page->allocate();
			}

			// Could not allocate to any existing pages,
			// create new page and allocate from there.
			PoolPage<T>* page = new PoolPage<T>(pageSize);
			pages.push_back(page);

			return page->allocate();
		}
		/// Deallocates the given element.
		inline bool deallocate(T* element) {
			const IntPtr address = reinterpret_cast<IntPtr>(element);

			for (PoolPage<T>* page : pages) {
				if (page->isInAddressSpace(address)) {
					page->deallocate(element);

					return true;
				}
			}

			return false;
		}

		/// Returns the count of pages.
		inline int32 pagesCount() const {
			return pages.size();
		}

		~PagePoolAllocator() {
			for (PoolPage<T>* page : pages) delete page;
		}
	};
}