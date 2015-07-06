#include "sani/platform/platform_config.hpp"

#if SANI_TARGET_PLATFORM == SANI_PLATFORM_WIN32

#include "sani/platform/window.hpp"
#include <xstring>

namespace sani {
	namespace graphics {

		class Window::Impl {
		public:
			// Simple flag to keep track about the 
			// state of the window.
			bool initialized;

			// Just store basic and long strings
			// to their own fields.
			
			LPCWSTR title;
			String cTitle;
			
			uint32 width;
			uint32 height;
			uint32 x;
			uint32 y;

			HINSTANCE hInstance;
			HWND hwnd;

			Impl() : initialized(false),
					 title(L"Win32Window"),
					 cTitle("Win32Window"),
					 width(800),
					 height(600),
					 x(300),
					 y(300) {
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
			switch (message) {
				// Close the application.
				case WM_DESTROY:
					PostQuitMessage(0);
					return 0;
				case WM_SIZE:
					// TODO: handle size changes.
					switch (wParam) {
						case SIZE_MAXHIDE:
						case SIZE_MAXIMIZED:
						case SIZE_MAXSHOW:
						case SIZE_MINIMIZED:
						case SIZE_RESTORED:
							break;
					}
					return 0;
			}

			// Get any errors.
			DWORD error = 0;
			while ((error = GetLastError()) != 0) {
				// TODO: report errors.
			}

			// Handle any messages the switch statement didn't.
			return DefWindowProc(hWnd, message, wParam, lParam);
		}

		void Window::moveWindow() {
			MoveWindow(impl->hwnd, impl->x, impl->y, impl->width, impl->height, TRUE);
		}

		// Public.

		const HWND& Window::getHandle() const {
			return impl->hwnd;
		}

		void Window::getTitle(String& title) const {
			title = impl->cTitle;
		}
		void Window::setTitle(const String& title) {
			const std::wstring stemp = std::wstring(title.begin(), title.end());

			impl->title = stemp.c_str();
			impl->cTitle = title;

			if (impl->initialized) {
				SetWindowText(impl->hwnd, impl->title);
			}
		}

		void Window::hide() {
			assert(impl->initialized);

			ShowWindow(impl->hwnd, SW_HIDE);
		}
		void Window::minimize() {
			assert(impl->initialized);

			ShowWindow(impl->hwnd, SW_MINIMIZE);
		}
		void Window::show() {
			assert(impl->initialized);

			ShowWindow(impl->hwnd, SW_SHOW);
		}

		void Window::setSize(const uint32 width, const uint32 height) {
			impl->width = width;
			impl->height = height;

			if (impl->initialized) moveWindow();
		}
		void Window::setWidth(const uint32 width) {
			impl->width = width;

			if (impl->initialized) moveWindow();
		}
		void Window::setHeight(const uint32 height) {
			impl->height = height;

			if (impl->initialized) moveWindow();
		}

		void Window::setPosition(const uint32 x, const uint32 y) {
			impl->x = x;
			impl->y = y;

			if (impl->initialized) moveWindow();
		}
		void Window::setX(const uint32 x) {
			impl->x = x;

			if (impl->initialized) moveWindow();
		}
		void Window::setY(const uint32 y) {
			impl->y = y;

			if (impl->initialized) moveWindow();
		}

		uint32 Window::getX() const {
			return impl->x;
		}
		uint32 Window::getY() const {
			return impl->y;
		}

		void Window::getClientBounds(math::Rectu32& rect) const {
		}
		void Window::getWindowBounds(math::Rectu32& rect) const {
		}

		inline uint32 Window::getWidth() {
			return impl->width;
		}
		inline uint32 Window::getHeight() {
			return impl->height;
		}

		bool Window::initialize() {
			assert(!impl->initialized);

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

			// TODO: open the window to the center of the display.
			// Create the window.
			impl->hwnd = CreateWindowEx(NULL,
										windowClass.lpszClassName,
										impl->title,
										WS_OVERLAPPED,
										300,
										300,
										impl->width,
										impl->height,
										NULL,
										NULL,
										impl->hInstance,
										NULL);

			// Could not create the window.
			if (GetLastError() != 0) {
				impl->initialized = false;
			} else {
				// Try to show the window.
				show();

				// Check for errors.
				impl->initialized = GetLastError() == 0;
			}

			// Return results.
			return impl->initialized;
		}

		Window::~Window() {
			delete impl;
		}
	}
}

#endif