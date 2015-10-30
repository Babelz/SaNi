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
			
			std::vector<T> memory;
			
			uint32 elementPointer;
			
			inline void checkSize(const uint32 newElementsCount) {
				if (bufferSizing == BufferSizing::Static) {
					if (elementPointer + newElementsCount > memory.size()) throw std::runtime_error("Buffer overflow");
				} else if (bufferSizing == BufferSizing::Dynamic) {
					if (elementPointer + newElementsCount > memory.size()) {
						const uint32 oldSize = memory.size();
						const uint32 newSize = memory.size() * 2;
						const uint32 diff = newSize - oldSize;

						memory.reserve(newSize);

						for (uint32 i = 0; i < diff; i++) memory.push_back(T());
					}
				}
			}
		public:
			Buffer(const uint32 initialSize, const BufferSizing bufferSizing) : bufferSizing(bufferSizing),
																			    elementPointer(0) {
				memory.reserve(initialSize);

				for (uint32 i = 0; i < initialSize; i++) memory.push_back(T());
			}
		
			/// Returns the type of the buffer. 
			inline BufferSizing getBufferSizing() const {
				return bufferSizing;
			}

			/// Push a given element to the buffer.
			inline void push(T element) {
				checkSize(1);

				memory[elementPointer] = element;
				
				elementPointer++;
			}
			/// Push given elements to the buffer.
			/// @param [in] elements elements to push
			/// @param [in] count count of elements to push
			inline void push(T* elements, const uint32 count) {
				checkSize(count);

				for (uint32 i = 0; i < count; i++) memory[i + elementPointer] = elements[i];

				elementPointer += count;
			}

			/// Returns the size of this buffer.
			inline uint32 getSize() const {
				return memory.size();
			}
			/// Returns the count of elements in this buffer.
			inline uint32 getElementsCount() const {
				return elementPointer;
			}

			/// Copies the contents of another buffer to this buffer.
			inline void copy(Buffer<T>& other) {
				checkSize(other.getElementsCount());

				push(other.pointer(), other.getElementsCount());
			}

			/// Returns pointer to the beginning of the buffer.
			inline T* pointer() {
				return &memory[0];
			}

			/// Clears the buffer.
			inline void clear() {
				elementPointer = 0;
			}
		
			~Buffer() {
			}
		};
	}
}