#include "sani/platform/platform_config.hpp"
#if SANI_TARGET_PLATFORM == SANI_PLATFORM_LINUX

#include "sani/platform/linux/file_manager_linux.hpp"
#include "sani/platform/file.hpp"
#include <sys/stat.h>
#include <dirent.h>

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
			assert(isFileOpen(path));

			FILE* handle = handles.at(path);
			size_t fsize = getFileSize(path);
			unsigned char* buffer = nullptr;
			if (nullTerminate) {
				buffer = (unsigned char*)malloc(fsize + 1);
				buffer[fsize] = '\0';
			} else {
				buffer = (unsigned char*)malloc(fsize );
			}

			size_t readBytes = fread(buffer, sizeof(unsigned char), fsize, handle);
			// Failed
			if (readBytes != fsize) {
				if (buffer) {
					free(buffer);
					buffer = nullptr;
				}
				fileSize = 0;
				return nullptr;
			}

			// Success
			fileSize = readBytes;
			return buffer;
		}

		String FileManagerLinux::getFileDataString(const String& path) const {
			size_t size = 0;
			unsigned char* buffer = getFileData(path, size, true);
			if (size == 0) {
				return "";
			}
			return String((const char*)buffer);
		}

		void FileManagerLinux::getBytes(std::vector<unsigned char>& out, const String& path, size_t offset, size_t count) const {
			assert(isFileOpen(path));
			FILE* handle = handles.at(path);
			fseek(handle, offset, SEEK_SET);
			out.resize(count);
			fread(out.data(), sizeof(unsigned char), count, handle);
			
		}

		void FileManagerLinux::listFiles(std::vector<String>& files, const String& path) const {
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

	}
}

#endif