#pragma once

#include "sani/types.hpp"

namespace sani {

	/// @class PreallocatedStaticArray preallocated_array.hpp "sani/core/memory/preallocated_array.hpp"
	/// @author voidbab
	///
	/// Preallocated static array that can be used with custom allocators.
	/// Works with heap and pool allocators only.
	template<typename Element, class Allocator>
	class PreallocatedStaticArray final {
	private:
		Element* elements;
		Allocator& allocator;

		const uint32 length;
		
		Element* allocate();
		void deallocate();
	public:
		PreallocatedStaticArray(const uint32 length, Allocator& allocator);

		/// Does bound check and returns the element pointed by the given index.
		Element* at(const uint32 index);
		Element* operator[](const uint32 index);

		decltype(auto) begin();
		decltype(auto) end();

		~PreallocatedStaticArray();

		PreallocatedStaticArray(PreallocatedStaticArray& other) = delete;
		PreallocatedStaticArray(PreallocatedStaticArray&& other) = delete;

		PreallocatedStaticArray& operator =(PreallocatedStaticArray& other) = delete;
		PreallocatedStaticArray& operator =(PreallocatedStaticArray&& other) = delete;
	};
}

#include "sani/core/memory/preallocated_array.hpp"