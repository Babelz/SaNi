#pragma once

#include "sani/graphics/buffer_sizing.hpp"
#include "sani/types.hpp"
#include <vector>

namespace sani {

	namespace graphics {

		/*
			TODO: Move impl to .cpp
		*/

		/// @class Buffer buffer.hpp "sani/graphics/buffer.hpp"
		/// @author voidbab
		///
		/// Represents a generic buffer.
		template<typename T>
		class Buffer {
		private:
			const BufferSizing bufferSizing;

			std::vector<T> memory;
			uint32 bufferPointer;
			uint32 size;
			
			inline void checkSize(const uint32 offset) {
				if (bufferSizing == BufferSizing::Static) {
					if (bufferPointer + offset > size) throw std::runtime_error("Buffer overflow");
				} else if (bufferSizing == BufferSizing::Dynamic) {
					if (bufferPointer + offset > size) {
						size *= 2;

						memory.resize(size);
					}
				}
			}
		public:
			Buffer(const uint32 initialSize, const BufferSizing bufferSizing) : bufferSizing(bufferSizing),
																			    bufferPointer(0),
																				size(initialSize) {
				memory.resize(size);
			}
		
			/// Returns the type of the buffer. 
			inline BufferSizing getBufferSizing() const {
				return bufferSizing;
			}

			/// Push a given element to the buffer.
			inline void push(T element) {
				checkSize(1);

				memory[bufferPointer] = element;
				
				bufferPointer++;
			}
			/// Push given elements to the buffer.
			/// @param [in] elements elements to push
			/// @param [in] count count of elements to push
			inline void push(const T* elements, const uint32 count) {
				checkSize(count);

				for (uint32 i = 0; i < count; i++) memory[i + bufferPointer] = elements[i];

				bufferPointer += count;
			}

			/// Applies given offset to this buffer.
			inline void offset(const uint32 offset) {
				checkSize(offset);

				bufferPointer += offset;
			}

			/// Returns the size of this buffer.
			inline uint32 getSize() const {
				return size;
			}
			/// Returns the location of the buffer pointer.
			inline uint32 getElementsCount() const {
				return bufferPointer;
			}

			/// Copies the contents of another buffer to this buffer.
			inline void copy(Buffer<T>& other) {
				checkSize(other.getBufferPointerLocation());

				push(other.data(), other.getBufferPointerLocation());
			}

			/// Returns pointer to the beginning of the buffer.
			inline T* data() {
				return memory.data();
			}

			/// Sets the buffer pointers value to zero.
			inline void resetBufferPointer() {
				bufferPointer = 0;
			}
		
			~Buffer() {
			}
		};
	}
}