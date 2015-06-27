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

		bool FileManager::isFileOpen(const String& path) const {
			return impl->isFileOpen(path);
		}

		bool FileManager::openFile(const String& path, const Filemode mode) {
			return impl->openFile(path, mode);
		}

		void FileManager::closeFile(const String& path) {
			impl->closeFile(path);
		}

		size_t FileManager::getFileSize(const String& path) const  {
			return impl->getFileSize(path);
		}

		unsigned char* FileManager::getFileData(const String& path, size_t& fileSize, bool nullTerminate /*= false*/) const {
			return impl->getFileData(path, fileSize, nullTerminate);
		}

		String FileManager::getFileDataString(const String& path) const  {
			return impl->getFileDataString(path);
		}

		void FileManager::getBytes(std::vector<unsigned char>& out, const String& path, size_t offset, size_t count) const {
			return impl->getBytes(out, path, offset, count);
		}


		void FileManager::listFiles(std::vector<String>& files, const String& path) const {
			return impl->listFiles(files, path);
		}

	}
}