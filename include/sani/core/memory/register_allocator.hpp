#pragma once

#include "sani/core/memory/page_pool_allocator.hpp"

#include <vector>
#include <stack>

namespace sani {

	/*
		TODO: this name?..
	*/

	/// @class RegisterAllocator register_allocator.hpp "sani/core/memory/register_allocator.hpp
	/// @author voidbab
	/// 
	/// Allocator that gives the location of the 
	/// allocated element to the user.
	template<class T>
	class RegisterAllocator final {
	private:
		PagePoolAllocator<T> allocator;
		std::stack<uint32> released;

		std::vector<T*> elements;
	public:
		RegisterAllocator(const int32 pageSize, const int32 initialPages);
		RegisterAllocator(const int32 pageSize);

		/// Returns the total amount of bytes used.
		uint64 getBytesUsed() const;
		/// Returns the current capacity of the allocator.
		uint64 getTotalBytes() const;

		/// Allocates new element.
		/// @param[in] outValue element that was allocated
		/// @param[in] outLocation elements location
		void allocate(T* outValue, uint32& outLocation);

		/// Deallocates element at the given location.
		/// @param[in] location location of the element that we want to deallocate
		void deallocate(const uint32 location);

		~RegisterAllocator() = default;

		RegisterAllocator(RegisterAllocator& other) = delete;
		RegisterAllocator(RegisterAllocator&& other) = delete;

		RegisterAllocator& operator =(RegisterAllocator& other) = delete;
		RegisterAllocator& operator =(RegisterAllocator&& other) = delete;
	};
}

#include "sani/core/memory/impl/register_allocator.hpp"