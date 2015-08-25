#include "sani/platform/platform_config.hpp"
#if SANI_TARGET_PLATFORM == SANI_PLATFORM_LINUX
#include "sani/platform/file_system.hpp"
#include <dirent.h>

namespace sani {
	namespace io {
		void FileSystem::listFiles(std::vector<String>& files, const String& path) const {
			DIR *d;
			struct dirent* dir;
			d = opendir(path.c_str());

			if (d) {
				while ((dir = readdir(d)) != NULL) {
					files.push_back(dir->d_name);
				}
				closedir(d);
			}
		}

		
		bool FileSystem::isAbsolutePath(const String& path) const {
			return !path.empty() && path.at(0) == '/';
		}
	}
}

#endif