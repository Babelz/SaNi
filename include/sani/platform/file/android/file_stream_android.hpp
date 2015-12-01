#pragma once
#include "sani/platform/platform_config.hpp"
#if SANI_TARGET_PLATFORM == SANI_PLATFORM_ANDROID

#include "sani/platform/file/file.hpp"
#include "sani/platform/file/file_stream.hpp"
#include "sani/platform/platform_config.hpp"
#include "sani/types.hpp"
#include <android/asset_manager.h>

namespace sani {
	namespace io {
		namespace priv {
			class AndroidFileStream : public FileStream {
			private:
				AAsset* asset;
			public:

				AndroidFileStream(const String& filePath, const Filemode mode, AAsset* asset);
				~AndroidFileStream();
				int64 read(unsigned char* buffer, const int32 size) const;

				int64 read(unsigned char* buffer, const int32 offset, const int32 size) const;

				uint32 write(const unsigned char* data, const int32 size) const;

				void seek(const SeekPosition seekpos, const long offset) const;

				void flush() const;
			};
		}
	}
}

#endif