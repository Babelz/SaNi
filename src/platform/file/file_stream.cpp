#include "sani/platform/file/file_stream.hpp"
#include "sani/debug.hpp"
#include <stdexcept>

namespace sani {
	namespace io {

		FileStream::FileStream(const String& filePath, const Filemode mode)
			: filePath(filePath), mode(mode) {}
		FileStream::~FileStream() {}

		namespace priv {
			_FileStream::_FileStream(const String& filePath, const Filemode mode, FILE* handle)
				: FileStream(filePath, mode), handle(handle) {

			}

			int64 _FileStream::read(unsigned char* buffer, const int32 size) const {
				// TODO check if the mode contains read
				SANI_ASSERT((static_cast<uint32>(mode)& static_cast<uint32>(Filemode::Read)) == static_cast<uint32>(Filemode::Read));
				int64 readBytes = fread(buffer, sizeof(unsigned char), size, handle);
				return readBytes;
			}

			uint32 _FileStream::write(const unsigned char* data, const int32 size) const {
				SANI_ASSERT((static_cast<uint32>(mode)& static_cast<uint32>(Filemode::Write)) == static_cast<uint32>(Filemode::Write) || (static_cast<uint32>(mode)& static_cast<uint32>(Filemode::Truncate)) == static_cast<uint32>(Filemode::Truncate));
				SANI_ASSERT(data != nullptr);
				uint32 wroteBytes = fwrite(data, sizeof(unsigned char), size, handle);
				return wroteBytes;
			}

			int64 _FileStream::read(unsigned char* buffer, const int32 offset, const int32 size) const {
				throw std::logic_error("Not implemented");
			}

			void _FileStream::seek(const SeekPosition seekpos, const long offset) const {
				int result = fseek(handle, offset, static_cast<int>(seekpos));
				if (!result) {
					throw std::runtime_error("File seeking failed");
				}
			}

			void _FileStream::flush() const {
				assert(static_cast<uint32>(mode)& static_cast<uint32>(Filemode::Write) || static_cast<uint32>(mode)& static_cast<uint32>(Filemode::Truncate));
				fflush(handle);
			}

			// TODO reference counting
			_FileStream::~_FileStream() {
				// flcose flushes the buffer
				fclose(handle);
			}
		}
	}
}



