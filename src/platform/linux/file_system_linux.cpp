#include "sani/platform/platform_config.hpp"
#if SANI_TARGET_PLATFORM == SANI_PLATFORM_LINUX

#include "sani/platform/file_system.hpp"
#include "sani/platform/file.hpp"


namespace sani {
	namespace io {

		FileSystem::FileSystem() {

		}

		FileSystem::~FileSystem() {

		}

		bool FileSystem::isFileOpen(const String& path) const {
			return handles.find(path) != handles.end();
		}

		bool FileSystem::openFile(const String& path, const Filemode mode) {
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

		bool FileSystem::isAbsolutePath(const String& path) const {
			return !path.empty() && path.at(0) == '/';
		}

		void FileSystem::closeFile(const String& path) {
			if (!isFileOpen(path)) return;

			FILE* handle = handles[path];
			fclose(handle);
			handles.erase(path);
		}

		unsigned char* FileSystem::getFileData(const String& path, size_t& fileSize, bool nullTerminate /*= false*/) const {
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

		void FileSystem::getBytes(std::vector<unsigned char>& out, const String& path, size_t offset, size_t count) const {
			assert(isFileOpen(path));
			FILE* handle = handles.at(path);
			fseek(handle, offset, SEEK_SET);
			out.resize(count);
			fread(out.data(), sizeof(unsigned char), count, handle);
			
		}

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

	}
}

#endif