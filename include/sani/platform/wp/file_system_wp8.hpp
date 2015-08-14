#include "sani/platform/platform_config.hpp"
#if SANI_TARGET_PLATFORM == SANI_PLATFORM_WP8
#include "sani/platform/file_system.hpp"
namespace sani {
	namespace io {
		class FileSystemWP8 : public FileSystem {
		public:
			FileSystemWP8() = default;
			~FileSystemWP8() = default;
			bool isAbsolutePath(const String& path) const;
			size_t getFileSize(const String& path) const;
			bool fileExists(const String& path) const;
			void listFiles(std::vector<String>& files, const String& path) const;
		};
	}
}


#endif