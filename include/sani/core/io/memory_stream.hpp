#pragma once
// TODO fix this 
#include "sani/platform/file/file_stream.hpp"
#include <vector>
namespace sani {
	namespace io {
		class MemoryStream : public Stream {
		private:
			std::vector<unsigned char> buffer;
			uint32 position = 0u;
			int64 dataSize = 0;
		public:
			MemoryStream() = default;
			virtual ~MemoryStream() = default;
			virtual int64 read(unsigned char* buffer, const int32 size) override;
			virtual int64 read(unsigned char* buffer, const int32 offset, const int32 size) override;
			virtual uint32 write(const unsigned char* data, const int32 size) override;
			virtual void seek(const SeekPosition seekpos, const long offset) override;
			virtual int64 size() override;
		};
	}
}