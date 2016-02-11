#pragma once

#include "sani/platform/platform_config.hpp"

namespace sani {

	namespace env {

#if SANI_PLATFORM_WIN32
		const char* NewLine = "\r\n";
#else
		const char* NewLine = "\n";
#endif
	}
}