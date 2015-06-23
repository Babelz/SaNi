#pragma once
#include "sani/platform/platform_config.hpp"
#if SANI_TARGET_PLATFORM == SANI_PLATFORM_WIN32
#include "sani/platform/base_file_manager.hpp"


namespace sani {
	namespace io {
		class FileManagerWin32 : public BaseFileManager {
		public:
			FileManagerWin32();
			~FileManagerWin32();
		};
	}
}

#endif