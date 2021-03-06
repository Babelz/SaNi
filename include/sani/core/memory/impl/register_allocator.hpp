#include "sani/core/memory/register_allocator.hpp"

namespace sani {

	template<class T>
	RegisterAllocator<T>::RegisterAllocator(const int32 pageSize, const int32 initialPages) : allocator(pageSize, initialPages) {
		elements.reserve(sizeof(T*) * pageSize * initialPages);
	}

	template<class T>
	RegisterAllocator<T>::RegisterAllocator(const int32 pageSize) : RegisterAllocator<T>::(pageSize, 1) {
	}

	template<class T>
	uint64 RegisterAllocator<T>::getBytesUsed() const {
		return allocator.getBytesUsed();
	}

	template<class T>
	uint64 RegisterAllocator<T>::getTotalBytes() const {
		return allocator.getTotalBytes();
	}

	template<class T>
	void RegisterAllocator<T>::allocate(T*& outValue, uint32& outLocation) {
		if (!released.empty()) {
			outLocation = released.top();
			released.pop();

			outValue = allocator.allocate();
			elements[outLocation] = outValue;
		} else {
			outLocation = static_cast<uint32>(elements.size());

			outValue = allocator.allocate();
			elements.push_back(outValue);
		}
	}

	template<class T>
	void RegisterAllocator<T>::deallocate(const uint32 location) {
		released.push(location);

		T* element = elements[location];
		elements[location] = nullptr;

		allocator.deallocate(element);
	}

	template<class T>
	const std::vector<T*>* RegisterAllocator<T>::allocatedElements() const {
		return &elements;
	}
}