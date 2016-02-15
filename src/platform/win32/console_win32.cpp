#include "sani/platform/platform_config.hpp"

#if SANI_TARGET_PLATFORM == SANI_PLATFORM_WIN32

#include "sani/platform/console.hpp"

/*
	Win32 impl of the console functions.
*/

namespace sani {
	
	void openSystemConsole(const uint32 width, const uint32 height, const int32 x, const int32 y) {
	}
	void openSystemConsole(const uint32 width, const uint32 height) {
	}

	void moveSystemConsole(const int32 x, const int32 y) {
	}

	void closeSystemConsole() {
	}
}

#endif