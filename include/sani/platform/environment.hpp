#pragma once

#include "sani/platform/platform_config.hpp"

namespace sani {

	namespace env {

#if SANI_PLATFORM_WINDOWS
		const char* NewLine = "\r\n";
#else
		const char* NewLine = "\n";
#endif
	}
}