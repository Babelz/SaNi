#include "sani/platform/platform_config.hpp"

#if SANI_TARGET_PLATFORM == SANI_PLATFORM_WIN32
#include "sani/platform/win32/file_manager_win32.hpp"
#endif

#if SANI_TARGET_PLATFORM == SANI_PLATFORM_LINUX
#include "sani/platform/linux/file_manager_linux.hpp"
#endif

#include "sani/platform/file_manager.hpp"

namespace sani {
	namespace io {
		
		FileManager::FileManager()
#if SANI_TARGET_PLATFORM == SANI_PLATFORM_WIN32
			: impl(new sani::io::FileManagerWin32()) 
#elif SANI_TARGET_PLATFORM == SANI_PLATFORM_LINUX
			: impl(new sani::io::FileManagerLinux())
#endif
		{ }

		FileManager::~FileManager() {
			delete impl;
			impl = nullptr;
		}

		bool FileManager::isAbsolutePath(const String& path) const  {
			return impl->isAbsolutePath(path);
		}

		bool FileManager::fileExists(const String& path) const {
			return impl->fileExists(path);
		}

		bool FileManager::isFileOpen(const File* file) const {
			return impl->isFileOpen(file);
		}

		bool FileManager::openFile(File** file, const String& path, const Filemode mode) {
			return impl->openFile(file, path, mode);
		}

		void FileManager::closeFile(File* file) {
			impl->closeFile(file);
		}

		size_t FileManager::getFileSize(const String& path) const  {
			return impl->getFileSize(path);
		}

		size_t FileManager::getFileSize(const File* file) const  {
			return impl->getFileSize(file);
		}

		unsigned char* FileManager::getFileData(const File* file, size_t& fileSize, bool nullTerminate /*= false*/) const {
			return impl->getFileData(file, fileSize, nullTerminate);
		}

		String FileManager::getFileDataString(const File* file) const  {
			return impl->getFileDataString(file);
		}


	}
}