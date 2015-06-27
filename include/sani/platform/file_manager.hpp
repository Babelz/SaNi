#pragma once

#include "sani/platform/base_file_manager.hpp"
#include "sani/platform/file.hpp"

namespace sani {
	namespace io {

		/// @class FileManager file_manager.hpp "sani/platform/file_manager.hpp"
		/// @author siquel
		/// 
		/// Cross platform wrapper for file i/o
		class FileManager : public BaseFileManager {
		private:
			BaseFileManager* impl;
		public:
			FileManager();
			~FileManager();

			bool fileExists(const String& path) const override;

			bool isFileOpen(const String& path) const override;

			bool openFile(const String& path, const Filemode mode) override;
			void closeFile(const String& path) override;
			bool isAbsolutePath(const String& path) const override;
			size_t getFileSize(const String& path) const override;
			unsigned char* getFileData(const String& path, size_t& fileSize, bool nullTerminate = false) const override;
			String getFileDataString(const String& path) const override;
			void getBytes(std::vector<unsigned char>& out, const String& path, size_t offset, size_t count) const override;
			void listFiles(std::vector<String>& files, const String& path) const override;
		};
	}
}

