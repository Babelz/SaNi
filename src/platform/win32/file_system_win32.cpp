#include "sani/platform/platform_config.hpp"
#if SANI_TARGET_PLATFORM == SANI_PLATFORM_WIN32
#include <windows.h>
#include "sani/platform/file_system.hpp"
#include "sani/platform/file.hpp"

namespace sani {
	namespace io {

		static std::wstring stringToWstring(const String& strUtf8) {
			std::wstring ret;
			if (!strUtf8.empty()) {
				int nNum = MultiByteToWideChar(CP_UTF8, 0, strUtf8.c_str(), -1, nullptr, 0);
				if (nNum) {
					WCHAR* wideCharString = new WCHAR[nNum + 1];
					wideCharString[0] = 0;

					nNum = MultiByteToWideChar(CP_UTF8, 0, strUtf8.c_str(), -1, wideCharString, nNum + 1);

					ret = wideCharString;
					delete[] wideCharString;
				}
			}
			return ret;
		}

		static String stringToMultiByte(const std::string& strUtf8) {
			String ret;
			if (!strUtf8.empty()) {
				std::wstring strWideChar = stringToWstring(strUtf8);
				int nNum = WideCharToMultiByte(CP_ACP, 0, strWideChar.c_str(), -1, nullptr, 0, nullptr, FALSE);
				if (nNum) {
					char* ansiString = new char[nNum + 1];
					ansiString[0] = 0;

					nNum = WideCharToMultiByte(CP_ACP, 0, strWideChar.c_str(), -1, ansiString, nNum + 1, nullptr, FALSE);

					ret = ansiString;
					delete[] ansiString;
				}
			}

			return ret;
		}

		static String wstringToString(const std::wstring& strWideChar) {
			if (!strWideChar.empty()) {
				int n = WideCharToMultiByte(CP_UTF8, 0, strWideChar.c_str(), -1, nullptr, 0, nullptr, FALSE);
				if (n) {					
					char* utf8String = new char[n + 1];
					utf8String[0] = 0;

					n = WideCharToMultiByte(CP_UTF8, 0, strWideChar.c_str(), -1, utf8String, n + 1, nullptr, FALSE);
					String ret(utf8String);
					delete[] utf8String;

					return ret;
				}
			}

			return "";
		}

		bool FileSystem::isAbsolutePath(const String& path) const  {
			// Should start with letter and second char should be : 
			if (path.length() < 2) return false;
			char c = path[0];
			return (((c >= 'a' && c <= 'z') || (c >= 'A' && c <= 'Z')) && path[1] == ':');
		}

		/*size_t FileSystemWin32::getFileSize(const String& path) const  {
			size_t fileSize;
			
			HANDLE fileHandle = ::CreateFileW(stringToWstring(path).c_str(), GENERIC_READ, FILE_SHARE_READ | FILE_SHARE_WRITE, NULL, OPEN_EXISTING, NULL, nullptr);
			if (fileHandle == INVALID_HANDLE_VALUE) {
				throw "Cant open file";
			}
			fileSize = ::GetFileSize(fileHandle, nullptr);
			CloseHandle(fileHandle);
			fileHandle = INVALID_HANDLE_VALUE;
			return fileSize;
		}*/
		/*
		bool FileSystem::fileExists(const String& path) const  {
			if (path.empty()) return false;
			DWORD attribs = GetFileAttributesW(stringToWstring(path).c_str());
			// Check if it is a file and exists
			if (attribs == INVALID_FILE_ATTRIBUTES || (attribs & FILE_ATTRIBUTE_DIRECTORY)) return false;

			// It exists
			return true;
		}*/

		void FileSystem::listFiles(std::vector<String>& files, const String& path) const {
			WIN32_FIND_DATA ffd;
			HANDLE handle = INVALID_HANDLE_VALUE;

			String dir;
			dir.reserve(path.size() + 2);
			dir = path + "\\*";
			handle = FindFirstFile(stringToWstring(dir).c_str(), &ffd);

			while (FindNextFile(handle, &ffd) != 0) {
				const String filename = wstringToString(ffd.cFileName); 

				if (filename == ".." || filename == ".") continue;
				
				files.push_back(filename);
			}

			FindClose(handle);
		}
	}
}


#endif