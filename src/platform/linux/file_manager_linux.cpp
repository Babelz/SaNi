#include "sani/platform/platform_config.hpp"
#if SANI_TARGET_PLATFORM == SANI_PLATFORM_LINUX

#include "sani/platform/linux/file_manager_linux.hpp"
#include "sani/platform/file.hpp"
#include <sys/stat.h>

namespace sani {
	namespace io {

		FileManagerLinux::FileManagerLinux() {

		}

		FileManagerLinux::~FileManagerLinux() {

		}

		bool FileManagerLinux::fileExists(const String& path) const {
			struct stat buffer;
			return (stat(path.c_str(), &buffer) == 0);
		}

		bool FileManagerLinux::isFileOpen(const String& path) const {
			return handles.find(path) != handles.end();
		}

		bool FileManagerLinux::openFile(const String& path, const Filemode mode) {
			if (isFileOpen(path)) return true;

			char access[5] = { 0 };
			// TODO binary
			if (mode & Filemode::Read && mode & Filemode::Write) {
				access[0] = 'r'; access[1] = 'a'; access[2] = '+';
			} else if (mode & Filemode::Read ) {
				access[0] = 'r'; 
			} else if (mode & Filemode::Write) {
				access[0] = 'a'; access[1] = '+';
			}
			FILE* handle = nullptr;
			handle = fopen(path.c_str(), access);

			if (!handle) return false;

			handles[path] = handle;

			// File open succeeded
			return true;
		}

		void FileManagerLinux::closeFile(const String& path) {
			if (!isFileOpen(path)) return;

			FILE* handle = handles[path];
			fclose(handle);
			handles.erase(path);
		}

		size_t FileManagerLinux::getFileSize(const String& path) const {
			// TODO if the file is opened already?
			struct stat statbuf;
			if (stat(path.c_str(), &statbuf) == -1) {
				// error
				return 0;
			}
			return statbuf.st_size;
		}

		unsigned char* FileManagerLinux::getFileData(const String& path, size_t& fileSize, bool nullTerminate /*= false*/) const {
			return nullptr;
		}

		String FileManagerLinux::getFileDataString(const String& path) const {
			return "";
		}

		void FileManagerLinux::getBytes(std::vector<unsigned char>& out, const String& path, size_t offset, size_t count) const {

		}

		void FileManagerLinux::listFiles(std::vector<String>& files, const String& path) const {

		}

	}
}

#endif