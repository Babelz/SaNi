#include "sani/platform/platform_config.hpp"
#if SANI_TARGET_PLATFORM == SANI_PLATFORM_WIN32
#include "sani/platform/win32/window_dx.hpp"

namespace sani {
	namespace graphics {
		WindowDX::WindowDX(const HINSTANCE hInstance, const uint32 width, const uint32 height, const int x, const int y, const String& title) {
			// Initialize the DirectX window.
			ZeroMemory(&windowClass, sizeof(WNDCLASSEX));
			
			windowClass.cbSize = sizeof(WNDCLASSEX);
			windowClass.style = CS_HREDRAW | CS_VREDRAW;
			windowClass.lpfnWndProc = this->windowProc;
			windowClass.hInstance = hInstance;
			windowClass.hCursor = LoadCursor(hInstance, IDC_ARROW);
			windowClass.lpszClassName = L"WindowClass";

			// Register the window class.
			RegisterClassEx(&windowClass);

			// Convert title to wstring.
			const std::wstring wstrTitle = std::wstring(title.begin(), title.end());

			// Create the window.
			handle = CreateWindowEx(
				NULL,
				L"WindowClass",
				wstrTitle.c_str(),
				WS_OVERLAPPEDWINDOW,
				x,
				y,
				width,
				height,
				NULL,
				NULL,
				hInstance,
				NULL);

			// Activates the window and displays it in its current size and position. 
			ShowWindow(handle, SW_SHOW);
		}

		int WindowDX::getX() const {
		}
		int WindowDX::getY() const {
		}

		uint32 WindowDX::getWidth() const {
		}
		uint32 WindowDX::getHeight() const {
		}

		void* WindowDX::getHandle() const {
		}

		WindowDX::~WindowDX() {
		}
	}
}

#endif

