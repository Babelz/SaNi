#include "sani/platform/file/file_stream.hpp"
#include "sani/debug.hpp"

namespace sani {
	namespace io {

		FileStream::FileStream(const String& filePath, const Filemode mode, FILE* handle) 
			: filePath(filePath), mode(mode), handle(handle) {

		}

		int64 FileStream::read(unsigned char* buffer, const int32 size) const {
			// TODO check if the mode contains read
			SANI_ASSERT((static_cast<uint32>(mode) & static_cast<uint32>(Filemode::Read)) == static_cast<uint32>(Filemode::Read));
			int64 readBytes = fread(buffer, sizeof(unsigned char), size, handle);
			return readBytes;
		}

		uint32 FileStream::write(const unsigned char* data, const int32 size) const {
			SANI_ASSERT((static_cast<uint32>(mode) & static_cast<uint32>(Filemode::Write)) == static_cast<uint32>(Filemode::Write) || (static_cast<uint32>(mode) & static_cast<uint32>(Filemode::Truncate)) == static_cast<uint32>(Filemode::Truncate));
			SANI_ASSERT(data != nullptr);
			uint32 wroteBytes = fwrite(data, sizeof(unsigned char), size, handle);
			return wroteBytes;
		}

		void FileStream::seek(const SeekPosition seekpos, const long offset) const {
			int result = fseek(handle, offset, static_cast<int>(seekpos));
			if (!result) {
				throw std::runtime_error("File seeking failed");
			}
		}

		void FileStream::flush() const {
			assert(static_cast<uint32>(mode) & static_cast<uint32>(Filemode::Write) || static_cast<uint32>(mode) & static_cast<uint32>(Filemode::Truncate));
			fflush(handle);
		}

		// TODO reference counting
		FileStream::~FileStream() {
			// flcose flushes the buffer
			fclose(handle);
		}

	}
}


