// This file should contain all common stuff
#include "sani/platform/platform_config.hpp"
#include "sani/platform/file_system.hpp"

// Needed only for nix systems
#if SANI_TARGET_PLATFORM != SANI_PLATFORM_WIN32 && SANI_TARGET_PLATFORM != SANI_PLATFORM_WP8
#include <sys/stat.h>
#include <dirent.h>
#endif

namespace sani {
	namespace io {
		String FileSystem::getFileDataString(const String& path) const  {
			size_t size = 0;
			unsigned char* buffer = getFileData(path, size, true);
			if (size == 0) {
				return "";
			}
			return String((const char*)buffer);
		}

		// Unix systems
#if SANI_TARGET_PLATFORM != SANI_PLATFORM_WIN32 && SANI_TARGET_PLATFORM != SANI_PLATFORM_WP8

		bool FileSystem::fileExists(const String& path) const {
			struct stat buffer;
			return (stat(path.c_str(), &buffer) == 0);
		}

		size_t FileSystem::getFileSize(const String& path) const {
			// TODO if the file is opened already?
			struct stat statbuf;
			if (stat(path.c_str(), &statbuf) == -1) {
				// error
				return 0;
			}
			return statbuf.st_size;
		}

#endif
	}
}






