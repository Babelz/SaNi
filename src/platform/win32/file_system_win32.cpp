#include "sani/platform/platform_config.hpp"
#if SANI_TARGET_PLATFORM == SANI_PLATFORM_WIN32 || SANI_TARGET_PLATFORM == SANI_PLATFORM_WP8

#include <windows.h>
#include "sani/platform/file_system.hpp"
#include "sani/platform/file.hpp"

namespace sani {
	namespace io {


		FileSystem::FileSystem() {

		}

		FileSystem::~FileSystem() {
			for (auto it = handles.begin(); it != handles.end(); it++) {
				::CloseHandle(handles[it->first]);
				handles[it->first] = INVALID_HANDLE_VALUE;
			}
		}

		bool FileSystem::isAbsolutePath(const String& path) const  {
			// Should start with letter and second char should be : 
			if (path.length() < 2) return false;
			char c = path[0];
			return (((c >= 'a' && c <= 'z') || (c >= 'A' && c <= 'Z')) && path[1] == ':');
		}

		bool FileSystem::openFile(const String& path, const Filemode mode) {
			// Check if we have file opened
			if (handles.find(path) != handles.end()) {
				// TODO do we need to close the handle?
				return true;
			}
			
			// We do not have file opened, lets open it
			WCHAR wszBuf[512] = { 0 };
			MultiByteToWideChar(CP_UTF8, 0, path.c_str(), -1, wszBuf, sizeof(wszBuf) / sizeof(wszBuf[0]));

			DWORD access;
			if (mode & Filemode::Read && mode & Filemode::Write) {
				access = GENERIC_READ | GENERIC_WRITE;
			}
			else if (mode & Filemode::Read) {
				access = GENERIC_READ;
			}
			else if (mode & Filemode::Write) {
				access = GENERIC_WRITE;
			}

			HANDLE handle = ::CreateFileW(wszBuf, access, FILE_SHARE_READ | FILE_SHARE_WRITE, NULL, OPEN_EXISTING, NULL, nullptr);
			// Did it succeed?
			if (handle == INVALID_HANDLE_VALUE) {
				return false;
			}
			
			handles[path] = handle;
			// File is open
			return true;
		}

		bool FileSystem::isFileOpen(const String& path) const  {
			return (handles.find(path) != handles.end());
		}

		void FileSystem::closeFile(const String& path) {
			if (isFileOpen(path)) {
				::CloseHandle(handles[path]);
				handles[path] = INVALID_HANDLE_VALUE;
				handles.erase(path);
			}
		}

		size_t FileSystem::getFileSize(const String& path) const  {
			size_t fileSize;
			// It is open
			if (handles.find(path) != handles.end()) {
				fileSize = ::GetFileSize(handles.at(path), nullptr);
			}
			else {
				// It's closed, so open and close it
				WCHAR wszBuf[512] = { 0 };
				MultiByteToWideChar(CP_UTF8, 0, path.c_str(), -1, wszBuf, sizeof(wszBuf) / sizeof(wszBuf[0]));

				HANDLE fileHandle = ::CreateFileW(wszBuf, GENERIC_READ, FILE_SHARE_READ | FILE_SHARE_WRITE, NULL, OPEN_EXISTING, NULL, nullptr);
				if (fileHandle == INVALID_HANDLE_VALUE) {
					throw "Cant open file";
				}
				fileSize = ::GetFileSize(fileHandle, nullptr);
				CloseHandle(fileHandle);
				fileHandle = INVALID_HANDLE_VALUE;
			}
			return fileSize;
		}

		bool FileSystem::fileExists(const String& path) const  {
			if (path.empty()) return false;

			WCHAR buf[512] = { 0 };
			MultiByteToWideChar(CP_UTF8, 0, path.c_str(), -1, buf, sizeof(buf) / sizeof(buf[0]));
			DWORD attribs = GetFileAttributesW(buf);
			// Check if it is a file and exists
			if (attribs == INVALID_FILE_ATTRIBUTES || (attribs & FILE_ATTRIBUTE_DIRECTORY)) return false;

			// It exists
			return true;
		}

		unsigned char* FileSystem::getFileData(const String& path, size_t& fileSize, bool nullTerminate /* = false */) const  {
			assert(isFileOpen(path));

			HANDLE handle = handles.at(path);

			size_t size = ::GetFileSize(handle, nullptr);
			DWORD sizeRead = 0;
			unsigned char* buffer = nullptr;

			if (nullTerminate) {
				buffer = (unsigned char*)malloc(size + 1);
				buffer[size] = '\0';
			}
			else {
				buffer = (unsigned char*)malloc(size);
			}
			
			BOOL success = ::ReadFile(handle, buffer, size, &sizeRead, nullptr);

			// Reading failed, lets delete buffers
			if (!success) {
				if (buffer) {
					free(buffer);
					buffer = nullptr;
				}
				fileSize = 0;
				return nullptr;
			}
			// The reading succeeded
			else {
				fileSize = size;
				return buffer;
			}
		}

		String FileSystem::getFileDataString(const String& path) const  {
			size_t size = 0;
			unsigned char* buffer = getFileData(path, size, true);
			if (size == 0) {
				return "";
			}
			return String((const char*)buffer);
		}

		void FileSystem::getBytes(std::vector<unsigned char>& out, const String& path, size_t offset, size_t count) const {
			HANDLE handle = handles.at(path);
			::SetFilePointer(handle, offset, nullptr, FILE_BEGIN);
			out.clear();
			out.resize(count);

			DWORD read = 0;
			::ReadFile(handle, out.data(), count, &read, nullptr);
		}

		void FileSystem::listFiles(std::vector<String>& files, const String& path) const {
			WIN32_FIND_DATA ffd;
			HANDLE handle = INVALID_HANDLE_VALUE;

			String dir;
			dir.reserve(path.size() + 2);
			dir = path + "\\*";
			std::wstring temp = std::wstring(dir.begin(), dir.end());
			handle = FindFirstFile(temp.c_str(), &ffd);

			while (FindNextFile(handle, &ffd) != 0) {
				std::wstring file(ffd.cFileName);
				files.push_back(String(file.begin(), file.end()));
			}
			FindClose(handle);
		}

	}
}


#endif