#pragma once

#include "sani/types.hpp"

#include "sani/platform/platform_config.hpp"

#if SANI_TARGET_PLATFORM != SANI_PLATFORM_WINDOWS
	#pragma error "file system utils not implemented for this platform!"
#endif

namespace sani {

	namespace io {

		/// Returns true if the given directory exists.
		bool directoryExists(const String& dir);
		
		/// Returns the directory of the executable.
		void rootDirectory(String& dir);
	}
}