#pragma once

#include "sani/platform/platform_config.hpp"
#if SANI_TARGET_PLATFORM == SANI_PLATFORM_LINUX

#include "sani/platform/file_manager.hpp"
#include <unordered_map>

namespace sani {
	namespace io {
		class FileManagerLinux : public BaseFileManager {
		private:
			std::unordered_map<String, FILE*> handles;
		public:
			FileManagerLinux();
			~FileManagerLinux();

			bool fileExists(const String& path) const override;
			bool isFileOpen(const String& path) const override;
			bool openFile(const String& path, const Filemode mode) override;
			void closeFile(const String& path) override;
			//bool isAbsolutePath(const String& path) const override;
			size_t getFileSize(const String& path) const override;
			unsigned char* getFileData(const String& path, size_t& fileSize, bool nullTerminate = false) const override;
			String getFileDataString(const String& path) const override;
			void getBytes(std::vector<unsigned char>& out, const String& path, size_t offset, size_t count) const override;
			void listFiles(std::vector<String>& files, const String& path) const override;
		};
	}
}


#endif