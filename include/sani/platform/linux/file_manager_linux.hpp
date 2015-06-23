#pragma once

#include "sani/platform/platform_config.hpp"
#if SANI_TARGET_PLATFORM == SANI_PLATFORM_LINUX

#include "sani/platform/file_manager.hpp"

namespace sani {
	namespace io {
		class FileManagerLinux : public BaseFileManager {
		public:
			FileManagerLinux();
			~FileManagerLinux();
		};
	}
}


#endif