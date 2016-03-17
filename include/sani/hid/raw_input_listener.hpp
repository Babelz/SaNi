#pragma once

#include "sani/platform/platform_config.hpp"
#if SANI_TARGET_PLATFORM == SANI_PLATFORM_WINDOWS
#include <Windows.h>
#endif

#include "sani/hid/keyboard.hpp"

namespace sani {
	namespace hid {
		/// Class that gathers the raw input from OS
		class RawInputListener {
		private:
		public:
#if SANI_TARGET_PLATFORM == SANI_PLATFORM_WINDOWS
			sani::hid::Key rawKeyToKeyCode(const UINT param);
			void handleRawInput(const MSG& msg);
#endif
			void init();
			void update();
		};
	}
}