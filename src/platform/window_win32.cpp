#include "sani/platform/window.hpp"
#include "sani/assert.hpp"

#if SANI_TARGET_PLATFORM == SANI_PLATFORM_WIN32

namespace sani {
	namespace graphics {
		
		/*
		 *		Some functions always require that the window is in initialized state.
		 *	    Should this be fixed?
		 */

		class Window::Impl {
		public:
			// Simple flag to keep track about the 
			// state of the window.
			bool initialized;
			bool isWindowOpen;
			bool isMinimized;

			// Just store basic and long strings
			// to their own fields.
			
			LPCWSTR title;
			String cTitle;
			
			int32 width;
			int32 height;
			int32 x;
			int32 y;

			HINSTANCE hInstance;
			HWND hWnd;

			Impl() : initialized(false),
					 isWindowOpen(false),
					 isMinimized(false),
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

		Window::Window(const HINSTANCE hInstance) : impl(new Impl()) {
			impl->hInstance = hInstance;
		}

		// Private.

		LRESULT CALLBACK Window::WndProc(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam) {
			Window* window;

			// Sent prior to the WM_CREATE message when a window is first created.
			if (message == WM_NCCREATE) {
				// Get instance pointer.
				window = static_cast<Window*>(reinterpret_cast<CREATESTRUCT*>(lParam)->lpCreateParams);

				// Just set last error to 0.
				SetLastError(0);

				// Try to set the window long ptr.
				if (!SetWindowLongPtr(hWnd, GWL_USERDATA, reinterpret_cast<LONG_PTR>(window))) {
					if (GetLastError() != 0) return FALSE;
				}
			}
			else {
				window = reinterpret_cast<Window*>(GetWindowLongPtr(hWnd, GWL_USERDATA));
			}

			// TODO: use window if needed.

			switch (message) {
				// Close the application.
				case WM_DESTROY:
					PostQuitMessage(0);
					DestroyWindow(hWnd);

					return 0;
				case WM_CREATE:
				{
					// Initialize for OpenGL, set pixel format.
					// TODO: select between OpenGL and DX.
					PIXELFORMATDESCRIPTOR pfd =
					{
						sizeof(PIXELFORMATDESCRIPTOR),
						1,
						PFD_DRAW_TO_WINDOW | PFD_SUPPORT_OPENGL | PFD_DOUBLEBUFFER,		// Flags.
						PFD_TYPE_RGBA,													// The kind of framebuffer. RGBA for palette.
						32,																// Colordepth of the framebuffer.
						0, 0, 0, 0, 0, 0,
						0,
						0,
						0,
						0, 0, 0, 0,
						24,																// Number of bits for the depth buffer.
						8,																// Number of bits for the stencil buffer.
						0,																// Number of Aux buffers in the framebuffer.
						PFD_MAIN_PLANE,
						0,
						0, 0, 0
					};

					// Handle to device.
					HDC hDC = GetDC(hWnd);

					// Set pixel format.
					int pixelFormatID = ChoosePixelFormat(hDC, &pfd);
					SetPixelFormat(hDC, pixelFormatID, &pfd);

					// TODO: add error handling.
					return 0;
				}
				case WM_SIZE:
					// Get new size of the window.
					RECT wndRect;

					GetWindowRect(window->impl->hWnd, &wndRect);

					window->impl->width = wndRect.right - wndRect.left;
					window->impl->height = wndRect.bottom - wndRect.top;

					return 0;
				case WM_MOVE:
					GetWindowRect(window->impl->hWnd, &wndRect);

					window->impl->x = wndRect.left;
					window->impl->y = wndRect.top;

					return 0;
			}

			// Handle any messages the switch statement didn't.
			return DefWindowProc(hWnd, message, wParam, lParam);
		}

		// Public.

		HWND Window::getHandle() const {
			assert(impl->initialized);

			return impl->hWnd;
		}

		String Window::getTitle() const {
			return impl->cTitle;
		}
		void Window::setTitle(const String& title) {
			const std::wstring stemp = std::wstring(title.begin(), title.end());

			impl->title = stemp.c_str();
			impl->cTitle = title;

			if (impl->initialized) {
				SetWindowText(impl->hWnd, impl->title);
			}
		}

		void Window::minimize() {
			assert(impl->initialized);

			if (impl->isMinimized) return;

			ShowWindow(impl->hWnd, SW_MINIMIZE);
			
			impl->isMinimized = true;
		}
		void Window::show() {
			assert(impl->initialized);

			if (impl->isMinimized) {
				ShowWindow(impl->hWnd, SW_RESTORE);

				impl->isMinimized = false;
			}
			else {
				ShowWindow(impl->hWnd, SW_SHOW);
			}
		}

		void Window::setSize(const int32 width, const int32 height) {
			if (impl->initialized) MoveWindow(impl->hWnd, impl->x, impl->y, width, height, TRUE);
			else {
				impl->width = width;
				impl->height = height;
			}
		}
		void Window::setWidth(const int32 width) {
			if (impl->initialized) MoveWindow(impl->hWnd, impl->x, impl->y, width, impl->height, TRUE);
			else {
				impl->width = width;
			}
		}
		void Window::setHeight(const int32 height) {
			if (impl->initialized) MoveWindow(impl->hWnd, impl->x, impl->y, impl->width, height, TRUE);
			else {
				impl->height = height;
			}
		}

		void Window::setPosition(const int32 x, const int32 y) {
			if (impl->initialized) MoveWindow(impl->hWnd, y, x, impl->width, impl->height, TRUE);
			else {
				impl->x = x;
				impl->y = y;
			}
		}
		void Window::setX(const int32 x) {
			if (impl->initialized) MoveWindow(impl->hWnd, x, impl->y, impl->width, impl->height, TRUE);
			else {
				impl->x = x;
			}
		}
		void Window::setY(const int32 y) {
			if (impl->initialized) MoveWindow(impl->hWnd, impl->x, y, impl->width, impl->height, TRUE);
			else {
				impl->y = y;
			}
		}

		int32 Window::getX() const {
			return impl->x;
		}
		int32 Window::getY() const {
			return impl->y;
		}

		uint32 Window::getClientWidth() const {
			assert(impl->initialized);

			RECT clntRect;

			GetClientRect(impl->hWnd, &clntRect);

			return clntRect.right- clntRect.left;
		}
		uint32 Window::getClientHeight() const {
			assert(impl->initialized);

			RECT clntRect;

			GetClientRect(impl->hWnd, &clntRect);

			return clntRect.bottom - clntRect.top;
		}

		inline int32 Window::getWidth() {
			return impl->width;
		}
		inline int32 Window::getHeight() {
			return impl->height;
		}

		void Window::listen() const {
			assert(impl->initialized);

			MSG msg;

			if (PeekMessage(&msg, NULL, 0, 0, PM_REMOVE)) {
				// translate keystroke messages into the right format
				TranslateMessage(&msg);

				// send the message to the WindowProc function
				DispatchMessage(&msg);

				impl->isWindowOpen = msg.message != WM_QUIT;
			}
		}

		bool Window::isOpen() const {
			assert(impl->initialized);

			return impl->isWindowOpen;
		}

		void Window::close() {
			assert(impl->initialized);

			if (!impl->isWindowOpen) return;

			impl->isWindowOpen = false;
		}

		bool Window::initialize() {
			assert(!impl->initialized);

			// Initialize the window.
			WNDCLASSEX windowClass;

			const size_t wndSize = sizeof(WNDCLASSEX);
			
			ZeroMemory(&windowClass, wndSize);
			WIN32_ASSERT();

			// Fill the struct.
			windowClass.cbSize = wndSize;
			windowClass.style = CS_HREDRAW | CS_VREDRAW;
			windowClass.lpfnWndProc = WndProc;
			windowClass.hInstance = impl->hInstance;
			windowClass.hCursor = LoadCursor(NULL, IDC_ARROW);
			windowClass.lpszClassName = L"WindowClass1";

			RegisterClassEx(&windowClass);
			WIN32_ASSERT();

			// TODO: set style to WS_OVERLAPPEDWINDOW for WinDX and 
			//		 CS_OWNDC for OpenGL. Create rendering API detection.

			// TODO: open the window to the center of the display.
			// Create the window.
			impl->hWnd = CreateWindowEx(NULL,
										windowClass.lpszClassName,
										impl->title,
										CS_OWNDC,
										impl->x,
										impl->y,
										impl->width,
										impl->height,
										NULL,
										NULL,
										impl->hInstance,
										this);

			WIN32_REQUIRE(impl->hWnd, L"failed to create window");

			// Set background to black.
			const HBRUSH brush = CreateSolidBrush(RGB(0, 0, 0));
			SetClassLongPtr(impl->hWnd, GCLP_HBRBACKGROUND, (LONG)brush);

			impl->initialized = true;
			impl->isWindowOpen = true;

			// Return results.
			return impl->initialized;
		}

		Window::~Window() {
			delete impl;
		}
	}
}

#endif