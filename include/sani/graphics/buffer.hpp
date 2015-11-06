#pragma once

#include "sani/graphics/buffer_sizing.hpp"
#include "sani/types.hpp"
#include <vector>

namespace sani {

	namespace graphics {

		/*
			Move impl to .cpp
		*/

		/// @class Buffer buffer.hpp "sani/graphics/buffer.hpp"
		/// @author voidbab
		///
		/// Represents a generic buffer.
		template<typename T>
		class Buffer {
		private:
			const BufferSizing bufferSizing;

			uint32 bufferPointer;
			uint32 size;
			T* memory;
			
			inline void checkSize(const uint32 offset) {
				if (bufferSizing == BufferSizing::Static) {
					if (bufferPointer + offset > size) throw std::runtime_error("Buffer overflow");
				} else if (bufferSizing == BufferSizing::Dynamic) {
					if (bufferPointer + offset > size) {
						const uint32 oldSize = size;
						const uint32 newSize = size * 2;

						/*
							WARNING: throws bad_alloc when trying to allocate 128mb of memory.
						*/

						T* newMemory = new T[newSize];
						std::move(memory, memory + oldSize, newMemory);

						delete memory;

						memory = newMemory;
						size = newSize;
					}
				}
			}
		public:
			Buffer(const uint32 initialSize, const BufferSizing bufferSizing) : bufferSizing(bufferSizing),
																			    bufferPointer(0),
																				memory(new T[initialSize]),
																				size(initialSize) {
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
				return &memory[0];
			}

			/// Sets the buffer pointers value to zero.
			inline void resetBufferPointer() {
				bufferPointer = 0;
			}
		
			~Buffer() {
				delete[] memory;
			}
		};
	}
}