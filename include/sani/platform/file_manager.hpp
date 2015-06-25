#pragma once

#include "sani/platform/base_file_manager.hpp"
#include "sani/platform/file.hpp"

namespace sani {
	namespace io {
		class FileManager : public BaseFileManager {
		private:
			BaseFileManager* impl;
		public:
			FileManager();
			~FileManager();

			bool fileExists(const String& path) const override;

			bool isFileOpen(const File* file) const override;

			bool openFile(File** file, const String& path, const Filemode mode) override;
			void closeFile(File* file) override;
			bool isAbsolutePath(const String& path) const override;
			size_t getFileSize(const String& path) const override;
			size_t getFileSize(const File* file) const override;
			unsigned char* getFileData(const File* file, size_t& fileSize, bool nullTerminate = false) const override;
			String getFileDataString(const File* file) const override;
			void getBytes(std::vector<unsigned char>& out, const File* file, size_t offset, size_t count) const override;
		};
	}
}

