#pragma once

#include "sani/types.hpp"
#include <iterator>

namespace sani {

	/// @class PreallocatedStaticArray preallocated_array.hpp "sani/core/memory/preallocated_array.hpp"
	/// @author voidbab
	///
	/// Preallocated static array that can be used with custom allocators.
	/// Works with heap and pool allocators only.
	template<typename ElementType, class AllocatorType>
	class PreallocatedStaticArray final {
	private:
		ElementType* elements;
		AllocatorType& allocator;

		const uint32 length;

		ElementType* heapAllocate();
		ElementType* poolAllocate();

		void heapDeallocate();
		void poolDeallocate();
	public:
		PreallocatedStaticArray(const uint32 length, AllocatorType& allocator);

		uint32 size() const;

		ElementType& operator[](const uint32 index);

		~PreallocatedStaticArray();

		PreallocatedStaticArray(PreallocatedStaticArray& other) = delete;
		PreallocatedStaticArray(PreallocatedStaticArray&& other) = delete;

		PreallocatedStaticArray& operator =(PreallocatedStaticArray& other) = delete;
		PreallocatedStaticArray& operator =(PreallocatedStaticArray&& other) = delete;
	};
}

#include "sani/core/memory/impl/preallocated_array.hpp"