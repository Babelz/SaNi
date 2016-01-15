#pragma once

#include "sani/graphics/buffer_sizing.hpp"
#include "sani/types.hpp"
#include <vector>

namespace sani {

	namespace graphics {

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
			
			inline void checkSize(const uint32 offset);
		public:
			Buffer(const uint32 initialSize, const BufferSizing bufferSizing);
		
			/// Returns the type of the buffer. 
			inline BufferSizing getBufferSizing() const;

			/// Push a given element to the buffer.
			inline void push(T element);
			/// Push given elements to the buffer.
			/// @param [in] elements elements to push
			/// @param [in] count count of elements to push
			inline void push(const T* elements, const uint32 count);

			/// Applies given offset to this buffer.
			inline void offset(const uint32 offset);

			/// Returns the size of this buffer.
			inline uint32 getSize() const;
			/// Returns the location of the buffer pointer.
			inline uint32 getElementsCount() const;

			/// Copies the contents of another buffer to this buffer.
			inline void copy(Buffer<T>& other);

			/// Returns pointer to the beginning of the buffer.
			inline T* data();

			/// Sets the buffer pointers value to zero.
			inline void resetBufferPointer();
		
			~Buffer();
		};
	}
}

#include "sani/graphics/impl/buffer.hpp"