#pragma once
#include "sani/platform/platform_config.hpp"
#if SANI_TARGET_PLATFORM == SANI_PLATFORM_WIN32
#include "sani/platform/base_file_manager.hpp"
#include <windows.h>
#include <sys/stat.h>

namespace sani {
	namespace io {

		/// @class FileManagerWin32 file_manager_win32.hpp "sani/platform/win32/file_manager_win32.hpp"
		/// @author siquel
		/// 
		/// Implements the WINAPI for file access
		class FileManagerWin32 : public BaseFileManager {
		protected:
			/// Contains the already opened files.
			/// The key is the path and value is the pointer to the file
			std::unordered_map<String, File*> files;
			/// Contains the file handles for already opened files
			/// The key is the path and value is the file handle
			std::unordered_map<String, HANDLE> handles;
		public:
			/// Default constructor
			FileManagerWin32();
			/// Destroys all the leftover handles and deletes file pointers
			virtual ~FileManagerWin32();
			bool isAbsolutePath(const String& path) const override;
			bool openFile(File** file, const String& path, const Filemode mode) override;
			bool isFileOpen(const File* file) const override;
			void closeFile(File* file) override;
			size_t getFileSize(const String& path) const override;
			size_t getFileSize(const File* file) const override;
			bool fileExists(const String& path) const override;
			unsigned char* getFileData(const File* file, size_t& fileSize, bool nullTerminate = false) const override;
			String getFileDataString(const File* file) const override;
		};
	}
}

#endif