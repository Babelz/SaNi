// This file should contain all common stuff
#include "sani/platform/platform_config.hpp"
#include "sani/platform/file/file_system.hpp"
#include "sani/platform/file/binary_reader.hpp"
#include "sani/platform/file/binary_writer.hpp"
#include "sani/debug.hpp"
#include <sys/stat.h>

namespace sani {
	namespace io {

		FileSystem::FileSystem() {

		}

		FileSystem::~FileSystem() {

		}

		bool FileSystem::isFileOpen(const String& path) const {
			return handles.find(path) != handles.end();
		}

		bool FileSystem::openFile(const String& path, const Filemode mode, FileStream** stream) {
			// don't support opening same file twice
			if (isFileOpen(path)) {
				return false;
			}

			char access[5] = { 0 };

			if (static_cast<uint32>(mode) & static_cast<uint32>(Filemode::Read) && static_cast<uint32>(mode) & static_cast<uint32>(Filemode::Write)) {
				access[0] = 'a'; access[1] = '+';  access[2] = 'b';
			}
			else if (static_cast<uint32>(mode) & static_cast<uint32>(Filemode::Truncate) && static_cast<uint32>(mode) & static_cast<uint32>(Filemode::Read)) {
				access[0] = 'w'; access[1] = '+'; access[2] = 'b';
			}
			else if (static_cast<uint32>(mode) & static_cast<uint32>(Filemode::Truncate)) {
				access[0] = 'w'; access[1] = 'b';
			}
			else if (static_cast<uint32>(mode) & static_cast<uint32>(Filemode::Read)) {
				access[0] = 'r'; access[1] = 'b';
			}
			else if (static_cast<uint32>(mode) & static_cast<uint32>(Filemode::Write)) {
				access[0] = 'a'; access[1] = 'b';
			}
			FILE* handle = nullptr;
			handle = fopen(path.c_str(), access);

			if (!handle) return false;

			handles[path] = new priv::FileStreamImpl(path, mode, handle);
			*stream = handles[path];

			// File open succeeded
			return true;
		}

		void FileSystem::closeFile(const String& path) {
			if (!isFileOpen(path)) return;

			FileStream* handle = handles[path];
			delete handle;
			handle = nullptr;
			handles.erase(path);
		}

		String FileSystem::getFileDataString(const String& path) const  {
			uint32 size = 0;
			unsigned char* buffer = getFileData(path, size, true);
			if (size == 0) {
				return "";
			}
			return String((const char*)buffer);
		}

		unsigned char* FileSystem::getFileData(const String& path, uint32& fileSize, bool nullTerminate /*= false*/) const {
			assert(isFileOpen(path));

			FileStream* handle = handles.at(path);
			uint32 fsize = getFileSize(path);
			unsigned char* buffer = nullptr;
			if (nullTerminate) {
				buffer = (unsigned char*)malloc(fsize + 1);
				buffer[fsize] = '\0';
			}
			else {
				buffer = (unsigned char*)malloc(fsize);
			}
			uint32 readBytes = 0;
			readBytes = handle->read(buffer, fsize);

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

		bool FileSystem::fileExists(const String& path) const {
			struct stat buffer;
			return (stat(path.c_str(), &buffer) == 0);
		}


		uint32 FileSystem::getFileSize(const String& path) const {
			struct stat statbuf;
			if (stat(path.c_str(), &statbuf) == -1) {
				// error
				return 0;
			}
			return statbuf.st_size;
		}
	}
}






