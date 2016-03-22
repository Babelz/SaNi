#pragma once

#include "sani/core/logging/log.hpp"
#include "sani/core/memory/preallocated_array.hpp"
#include "sani/core/memory/heap_allocator.hpp"
#include "sani/core/memory/page_pool_allocator.hpp"

namespace sani {

	template<typename ElementType, class AllocatorType>
	PreallocatedStaticArray<ElementType, AllocatorType>::PreallocatedStaticArray(const uint32 length, AllocatorType& allocator) : length(length),
																													              allocator(allocator) {
		if		(typeid(AllocatorType) == typeid(HeapAllocator))					elements = heapAllocate();
		else if (typeid(AllocatorType) == typeid(PagePoolAllocator<ElementType>))	elements = poolAllocate();
		else {
			FLOG_ERR(log::OutFlags::All, "invalid allocator type");

			std::abort();
		}
	}

	template<typename ElementType, class AllocatorType>
	ElementType* PreallocatedStaticArray<ElementType, AllocatorType>::heapAllocate() {
		auto* const concreteAllocator = reinterpret_cast<HeapAllocator* const>(&allocator);

		return concreteAllocator->allocate<ElementType>(length);
	}
	template<typename ElementType, class AllocatorType>
	ElementType* PreallocatedStaticArray<ElementType, AllocatorType>::poolAllocate() {
		auto* const concreteAllocator = reinterpret_cast<PagePoolAllocator<ElementType>* const>(&allocator);

		return concreteAllocator->allocate(length);
	}

	template<typename ElementType, class AllocatorType>
	void PreallocatedStaticArray<ElementType, AllocatorType>::heapDeallocate() {
		auto* const concreteAllocator = reinterpret_cast<HeapAllocator* const>(&allocator);

		concreteAllocator->deallocate<ElementType>(elements, length);
	}
	template<typename ElementType, class AllocatorType>
	void PreallocatedStaticArray<ElementType, AllocatorType>::poolDeallocate() {
		auto* const concreteAllocator = reinterpret_cast<PagePoolAllocator<ElementType>* const>(&allocator);

		concreteAllocator->deallocate(elements, length);
	}

	template<typename ElementType, class AllocatorType>
	uint32 PreallocatedStaticArray<ElementType, AllocatorType>::size() const {
		return length;
	}

	template<typename ElementType, class AllocatorType>
	ElementType& PreallocatedStaticArray<ElementType, AllocatorType>::operator[](const uint32 index) {
		return elements[index];
	}

	template<typename ElementType, class AllocatorType>
	PreallocatedStaticArray<ElementType, AllocatorType>::~PreallocatedStaticArray() {
		if		(typeid(AllocatorType) == typeid(HeapAllocator))					heapDeallocate();
		else if (typeid(AllocatorType) == typeid(PagePoolAllocator<ElementType>))	poolDeallocate();
	}
}