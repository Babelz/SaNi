#include "sani/platform/file/file_stream.hpp"
#include "sani/debug.hpp"
#include <stdexcept>

namespace sani {
	namespace io {

		FileStream::FileStream(const String& filePath, const Filemode mode)
			: filePath(filePath), mode(mode) {}
		FileStream::~FileStream() {}

		namespace priv {
			FileStreamImpl::FileStreamImpl(const String& filePath, const Filemode mode, FILE* handle)
				: FileStream(filePath, mode), handle(handle) {

			}

			uint32 FileStreamImpl::read(unsigned char* buffer, const uint32 size) {
				// TODO check if the mode contains read
				SANI_ASSERT((static_cast<uint32>(mode)& static_cast<uint32>(Filemode::Read)) == static_cast<uint32>(Filemode::Read));
				uint32 readBytes = fread(buffer, sizeof(unsigned char), size, handle);
				return readBytes;
			}

			uint32 FileStreamImpl::write(const unsigned char* data, const uint32 size) {
				SANI_ASSERT((static_cast<uint32>(mode)& static_cast<uint32>(Filemode::Write)) == static_cast<uint32>(Filemode::Write) || (static_cast<uint32>(mode)& static_cast<uint32>(Filemode::Truncate)) == static_cast<uint32>(Filemode::Truncate));
				SANI_ASSERT(data != nullptr);
				uint32 wroteBytes = fwrite(data, sizeof(unsigned char), size, handle);
				return wroteBytes;
			}

			uint32 FileStreamImpl::read(unsigned char* buffer, const int32 offset, const uint32 size) {
				throw std::logic_error("Not implemented");
			}

			void FileStreamImpl::seek(const SeekPosition seekpos, const long offset) {
				int result = fseek(handle, offset, static_cast<int>(seekpos));
				if (!result) {
					throw std::runtime_error("File seeking failed");
				}
			}

			void FileStreamImpl::flush() {
				assert(static_cast<uint32>(mode)& static_cast<uint32>(Filemode::Write) || static_cast<uint32>(mode)& static_cast<uint32>(Filemode::Truncate));
				fflush(handle);
			}

			uint32 FileStreamImpl::size() {
				long current = ftell(handle);
				fseek(handle, 0L, SEEK_END);
				uint32 size = ftell(handle);
				fseek(handle, current, SEEK_SET);
				return size;
			}

			// TODO reference counting
			FileStreamImpl::~FileStreamImpl() {
				// flcose flushes the buffer
				fclose(handle);
			}
		}
	}
}



