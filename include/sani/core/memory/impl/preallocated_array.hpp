#pragma once

#include "sani/core/memory/page_pool_allocator.hpp"
#include "sani/core/memory/heap_allocator.hpp"

namespace sani {

	template<typename Element, class Allocator>
	PreallocatedStaticArray::PreallocatedStaticArray(const uint32 length, Allocator& allocator) : length(length),
																								  allocator(allocator) {
	}

	template<typename Element, class Allocator>
	void PreallocatedStaticArray::deallocate() {
	}

	template<typename Element, class Allocator>
	Element* PreallocatedStaticArray::at(const uint32 index) {
	}
	template<typename Element, class Allocator>
	Element* PreallocatedStaticArray::operator[](const uint32 index) {
	}

	template<typename Element, class Allocator>
	decltype(auto) PreallocatedStaticArray::begin() {
		return std::begin(elements);
	}
	template<typename Element, class Allocator>
	decltype(auto) PreallocatedStaticArray::end() {
		return std::end(elements);
	}

	template<typename Element, class Allocator>
	PreallocatedStaticArray::~PreallocatedStaticArray() {
		allocator.deallocate(elements);
	}
}