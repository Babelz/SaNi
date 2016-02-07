#pragma once

#include "sani/platform/platform_config.hpp"
#if SANI_TARGET_PLATFORM == SANI_PLATFORM_WIN32
#include <Windows.h>
#endif

#include "sani/hid/keyboard.hpp"

namespace sani {
	namespace hid {
		/// Class that gathers the raw input from OS
		class RawInputListener {
		public:
#if SANI_TARGET_PLATFORM == SANI_PLATFORM_WIN32
			sani::hid::Key rawKeyToKeyCode(const UINT param);
			void handleRawInput(const MSG& msg);
#endif
			void init();
			void update();
		};
	}
}