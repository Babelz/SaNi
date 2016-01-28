#include "sani/core/memory/page_pool_allocator.hpp"

namespace sani {

	template <class T>
	PagePoolAllocator<T>::PagePoolAllocator(const int32 pageSize, const int32 initialPages) : pageSize(pageSize) {
		initialize(initialPages);
	}
	template <class T>
	PagePoolAllocator<T>::PagePoolAllocator(const int32 pageSize) : pageSize(pageSize) {
		initialize(1);
	}
	template <class T>
	PagePoolAllocator<T>::PagePoolAllocator() : pageSize(32) {
		initialize(1);
	}

	template <class T>
	bool PagePoolAllocator<T>::isInAddressSpace(T* element) const {
		const IntPtr address = reinterpret_cast<IntPtr>(element);

		for (const PoolPage<T>* page : pages) if (page->isInAddressSpace(address)) return true;

		return false;
	}

	template <class T>
	void PagePoolAllocator<T>::initialize(const uint32 initialPages) {
		for (uint32 i = 0; i < initialPages; i++) pages.push_back(new PoolPage<T>(pageSize));
	}

	template <class T>
	T* PagePoolAllocator<T>::allocate() {
		for (PoolPage<T>* page : pages) {
			if (page->canAllocate()) return page->allocate();
		}

		// Could not allocate to any existing pages,
		// create new page and allocate from there.
		PoolPage<T>* page = new PoolPage<T>(pageSize);
		pages.push_back(page);

		return page->allocate();
	}
	template <class T>
	bool PagePoolAllocator<T>::deallocate(T* element) {
		const IntPtr address = reinterpret_cast<IntPtr>(element);

		for (PoolPage<T>* page : pages) {
			if (page->isInAddressSpace(address)) {
				page->deallocate(element);

				return true;
			}
		}

		return false;
	}

	template <class T>
	int32 PagePoolAllocator<T>::pagesCount() const {
		return pages.size();
	}

	template <class T>
	uint64 PagePoolAllocator<T>::getBytesUsed() const {
		uint64 bytesUsed = 0;

		for (PoolPage<T>* page : pages) bytesUsed += page->getBytesUsed();

		return bytesUsed;
	}
	template <class T>
	uint64 PagePoolAllocator<T>::getTotalBytes() const {
		return sizeof(T) * pages.size() * pageSize;
	}

	template <class T>
	PagePoolAllocator<T>::~PagePoolAllocator() {
		for (PoolPage<T>* page : pages) delete page;
	}
}