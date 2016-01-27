#include "sani/core/io/memory_stream.hpp"
#include "sani/debug.hpp"

namespace sani {
	namespace io{

		uint32 MemoryStream::read(unsigned char* buffer, const uint32 size)  {
			std::memcpy(buffer, this->buffer.data() + position, size);
			position += size;
			// hmm how?
			return size;
		}

		uint32 MemoryStream::read(unsigned char* buffer, const int32 offset, const uint32 size)  {
			throw std::logic_error("not implemented");
		}

		uint32 MemoryStream::write(const unsigned char* data, const uint32 size)  {
			// TODO fix this, demo hax
			
			if ((dataSize + size) >= buffer.size()) {
				uint32 newSize = static_cast<uint32>(dataSize + size * 2u);
				//buffer.resize(newSize);
			}
			buffer.insert(
				buffer.begin() + position, 
				data, 
				data + size);
			dataSize += size;
			position += size;
			return static_cast<uint32>(size);
		}

		void MemoryStream::seek(const SeekPosition seekpos, const long offset)  {
			// TODO is this correct`?
			if (seekpos == SeekPosition::Begin) {
				position = offset;
			}
			else if (seekpos == SeekPosition::End) {
				position = size() + offset;
			}
			else {
				position += offset;
			}
		}

		uint32 MemoryStream::size()  {
			return dataSize;
		}

		void MemoryStream::flush() {
			throw std::logic_error("not implemented");
		}

	}
}