#include "sani/graphics/inl/buffer.inl"

namespace sani {

	namespace graphics {

		template<typename T>
		Buffer<T>::Buffer(const uint32 initialSize, const BufferSizing bufferSizing) : bufferSizing(bufferSizing),
																					   bufferPointer(0),
																					   size(initialSize) {
			memory.resize(size);
		}
		
		template<typename T>
		Buffer<T>::~Buffer() {
		}
	}
}
