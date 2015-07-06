#include "sani/platform/platform_config.hpp"

#if SANI_TARGET_PLATFORM == SANI_PLATFORM_WIN32

#include "sani/platform/window.hpp"

namespace sani {
	namespace graphics {

		class Window::Impl {
		public:
			bool initialized;

			String title;
			String name;

			uint32 width;
			uint32 height;

			HINSTANCE hInstance;
			HWND hwnd;

			Impl() : width(0),
					 height(0),
					 title(String("Win32Window")),
					 initialized(false) {
			}

			~Impl() {
			}
		};

		Window::Window(const HINSTANCE& hInstance, const uint32 width, const uint16 height) : impl(new Impl()) {
			impl->width = width;
			impl->height = height;
			impl->hInstance = hInstance;
		}

		// Private.

		LRESULT CALLBACK Window::WindowProc(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam) {
			return 0;
		}

		// Public.

		const HWND& Window::getHandle() const {
			return impl->hwnd;
		}

		void Window::setTitle(const String& title) {
			impl->title = title;

			if (impl->initialized) {
				// TODO: change the title.
			}
		}

		const inline uint32 Window::getWidth() {
			return impl->width;
		}
		const inline uint32 Window::getHeight() {
			return impl->height;
		}

		bool Window::initialize() {
			if (impl->initialized) {
				// TODO: log error, double initialization.
			}

			// Initialize the window.
			WNDCLASSEX windowClass;

			const size_t wndSize = sizeof(WNDCLASSEX);
			
			ZeroMemory(&windowClass, wndSize);

			// Fill the struct.
			windowClass.cbSize = wndSize;
			windowClass.style = CS_HREDRAW | CS_VREDRAW;
			windowClass.lpfnWndProc = WindowProc;
			windowClass.hInstance = impl->hInstance;
			windowClass.hCursor = LoadCursor(NULL, IDC_ARROW);
			windowClass.lpszClassName = L"WindowClass1";

			RegisterClassEx(&windowClass);

			return false;
		}

		Window::~Window() {
			delete impl;
		}
	}
}

#endif



