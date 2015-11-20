#include "sani/platform/platform_config.hpp"
#if SANI_TARGET_PLATFORM == SANI_PLATFORM_ANDROID

#include "sani/platform/file/android/file_stream_android.hpp"
#include <stdexcept>
#include "sani/platform/platform_exception.hpp"
namespace sani {
	namespace io {
		namespace priv {
			AndroidFileStream::AndroidFileStream(const String& filePath, const Filemode mode, AAsset* asset)
				: FileStream(filePath, mode), asset(asset) {

			}

			AndroidFileStream::~AndroidFileStream() {
				//AAsset_close(asset);
			}

			int64 AndroidFileStream::read(unsigned char* buffer, const int32 size) const {
				int read = AAsset_read(asset, buffer, size);
				return read;
			}

			int64 AndroidFileStream::read(unsigned char* buffer, const int32 offset, const int32 size) const {
				throw std::logic_error("Not implemented");
				//AAsset_seek(asset, 
			}

			uint32 AndroidFileStream::write(const unsigned char* data, const int32 size) const {
				throw sani::UnsupportedOperation("Android does not support writing files inside APK");
			}

			void AndroidFileStream::seek(const SeekPosition seekpos, const long offset) const {
				off_t result = AAsset_seek(asset, offset, static_cast<int>(seekpos));
				if (!result) {
					throw std::runtime_error("File seeking failed");
				}
			}

			void AndroidFileStream::flush() const {
				throw sani::UnsupportedOperation("Android does not support writing files inside APK");
			}
		}
	}
}

#endif