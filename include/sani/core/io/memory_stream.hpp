#pragma once

#include "sani/platform/file/file_stream.hpp"
#include <vector>

namespace sani {
	
	namespace io {
		
		/// @class MemoryStream memory_stream.hpp "sani/core/io/memory_stream.hpp"
		/// @author siquel
		///
		/// Stream that is used writing to "memory"
		class MemoryStream : public Stream {
		private:
			// The buffer where to output
			unsigned char* buffer;
			// Current position in stream
			uint32 position;
			// How large the buffer is
			uint32 dataSize;
			// The element count 
			uint32 elements;
		public:
			/// Constructs new memory stream
			MemoryStream();
			
			/// Reads size amount of bytes from buffer
			///
			/// @param buffer the buffer where to read
			/// @param size how many bytes
			/// @returns the amount of bytes read
			virtual uint32 read(unsigned char* buffer, const uint32 size) override;

			/// Reads size amount of bytes from buffer from the offset
			///
			/// @param buffer the buffer where to read
			/// @param offset the offset where to start reading
			/// @param size how many bytes
			/// @returns the amount of bytes read
			virtual uint32 read(unsigned char* buffer, const int32 offset, const uint32 size) override;

			/// Writes the data to buffer, uses std::memcpy to copy the data
			/// 
			/// @param data Pointer to the data store
			/// @param size How large is the data store
			/// @returns how many bytes were written
			virtual uint32 write(const unsigned char* data, const uint32 size) override;

			/// Seeks in the stream to the specified offset
			///
			/// @param seekpos Where to start seeking
			/// @param offset How many bytes to travel from starting seek position
			virtual void seek(const SeekPosition seekpos, const long offset) override;
			
			/// Gets the size of the buffer
			///
			/// @returns The size of buffer
			virtual uint32 size() override;

			virtual void flush() override;
			
			/// Deconstructs memory stream and frees the buffer
			virtual ~MemoryStream();
		};
	}
}