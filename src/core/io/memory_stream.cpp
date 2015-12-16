#include "sani/core/io/memory_stream.hpp"

namespace sani {
	namespace io{

		int64 MemoryStream::read(unsigned char* buffer, const int32 size)  {
			throw std::logic_error("not implemented");
		}

		int64 MemoryStream::read(unsigned char* buffer, const int32 offset, const int32 size)  {
			throw std::logic_error("not implemented");
		}

		uint32 MemoryStream::write(const unsigned char* data, const int32 size)  {
			// TODO fix this, demo hax
			
			if ((dataSize + size) >= buffer.size()) {
				uint32 newSize = static_cast<uint32>(dataSize + size * 2u);
				buffer.resize(newSize);
			}
			return 0;
		}

		void MemoryStream::seek(const SeekPosition seekpos, const long offset)  {
			throw std::logic_error("not implemented");
		}

		int64 MemoryStream::size()  {
			throw std::logic_error("not implemented");
		}

	}
}