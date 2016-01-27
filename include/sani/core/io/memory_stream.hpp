#pragma once

#include "sani/platform/file/file_stream.hpp"
#include <vector>

namespace sani {
	
	namespace io {
		
		// TODO: document and fix.
		class MemoryStream : public Stream {
		private:
			std::vector<unsigned char> buffer;
			uint64 position = 0u;
			uint32 dataSize = 0;
		public:
			MemoryStream() = default;
			
			virtual uint32 read(unsigned char* buffer, const uint32 size) override;
			virtual uint32 read(unsigned char* buffer, const int32 offset, const uint32 size) override;

			virtual uint32 write(const unsigned char* data, const uint32 size) override;

			virtual void seek(const SeekPosition seekpos, const long offset) override;
			
			virtual uint32 size() override;

			virtual void flush() override;

			virtual ~MemoryStream() = default;	
		};
	}
}