#include "sani/platform/platform_config.hpp"

#if SANI_TARGET_PLATFORM == SANI_PLATFORM_WINDOWS

#include "sani/platform/file/file_system_utils.hpp"

#include <sys/types.h>
#include <sys/stat.h>
#include <windows.h>

namespace sani {

	namespace io {
		
		bool directoryExists(const String& dir) {
			const char* cstr = dir.c_str();

			struct stat info;

			if (stat(cstr, &info) != 0)			return false;
			else if (info.st_mode & S_IFDIR)	return true;
			else								return false;
		}

		void rootDirectory(String& dir) {
			TCHAR szFileName[MAX_PATH];

			GetModuleFileName(NULL, szFileName, MAX_PATH);

			std::wstring wstr(szFileName);

			dir = String(wstr.begin(), wstr.end());
			dir = dir.substr(0, dir.find_last_of("\\"));
		}
	}
}

#endif