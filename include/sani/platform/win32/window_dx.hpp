#pragma once
#include "sani/platform/platform_config.hpp"
#if SANI_TARGET_PLATFORM == SANI_PLATFORM_WIN32
#include <windows.h>
#include "sani/platform/base_window.hpp"

namespace sani {
	namespace graphics {

		/// @class WindowDX window_dx.hpp "sani/win32/window_dx.hpp"
		/// @author voidbab
		/// 
		/// DirectX window implementation.
		class WindowDX : public Window {
		private:
			HWND handle;				// Windows handle.
			WNDCLASSEX windowClass;		// Information about this window.
		public:
			WindowDX(const uint32 width, const uint32 height, const int x, const int y, const String& title);

			virtual int getX() const override;
			virtual int getY() const override;

			virtual uint32 getWidth() const override;
			virtual uint32 getHeight() const override;

			virtual void* getHandle() const override;

			virtual ~WindowDX() override;
		};
	}
}

#endif