#pragma once
#include "sani/platform/platform_config.hpp"
#if SANI_TARGET_PLATFORM == SANI_PLATFORM_WIN32
#include <windows.h>
#include "sani/platform/window.hpp"

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

			LRESULT CALLBACK windowProc(const HWND hWnd, const UINT message, const WPARAM wParam, const LPARAM lParam);
		public:
			/// Creates new window.
			/// @param[in] width Initial width of the window in pixels.
			/// @param[in] height Initial height of the window in pixels.
			/// @param[in] title Initial title of the window.
			WindowDX(const HINSTANCE hInstance, const uint32 width, const uint32 height, const int x, const int y, const String& title);

			int getX() const override;
			int getY() const override;

			uint32 getWidth() const override;
			uint32 getHeight() const override;
			
			void* getHandle() const override;

			~WindowDX() override;
		};
	}
}

#endif