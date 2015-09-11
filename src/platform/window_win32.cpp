#include "sani/platform/window.hpp"
#include "sani/assert.hpp"

/*
	Common impl class. Contains all fields
	that are common between all platform windows.
*/

namespace sani {
	namespace graphics {

		// Common implementation. Contains basic 
		// information about the window.
		class Window::Cimpl {
		public:
			String title;

			bool initialized;
			bool isWindowOpen;
			bool isMinimized;

			int32 width;
			int32 height;
			int32 x;
			int32 y;

			Cimpl() : title("SaNi-Game"),
					  initialized(false),
					  isWindowOpen(false),
					  isMinimized(false),
					  width(0),
					  height(0),
					  x(0),
					  y(0) {
			}

			~Cimpl() {
			}
		};
	}
}

#if SANI_TARGET_PLATFORM == SANI_PLATFORM_WIN32

namespace sani {
	namespace graphics {
		
		/*
		 *		Some functions always require that the window is in initialized state.
		 *	    Should this be fixed?
		 */

		class Window::Impl {
		public:
			/*
				Win32 stuff.
			*/
			HINSTANCE hInstance;
			HWND hWnd;

			LPCWSTR lpcwTitle;
			
			Window::Cimpl cImpl;

			Impl() : lpcwTitle(L"SaNi-Game") {
			}

			~Impl() {
			}
		};

		Window::Window(const HINSTANCE hInstance, const uint32 width, const uint32 height) : impl(new Impl()) {
			impl->hInstance = hInstance;
			impl->cImpl.width = width;
			impl->cImpl.height = height;

			/*
				TODO: add calling logic.
			*/

			SANI_INIT_EVENT(onClosing, void(Window&));
			SANI_INIT_EVENT(onClosed, void(Window&));
			SANI_INIT_EVENT(onMinimize, void(Window&));
			SANI_INIT_EVENT(onWindowed, void(Window&));
			SANI_INIT_EVENT(onFullscreen, void(Window&));
			SANI_INIT_EVENT(onMoved, void(Window&, int, int, int, int));
			SANI_INIT_EVENT(onResize, void(Window&, int, int, int, int));
		}

		// Private.

		LRESULT CALLBACK Window::WndProc(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam) {
			/*
				TODO: window goes to black and stops 
					  rendering when moved, fix it.

					  When moving or resizing the window, 
					  windows blocks the calling thread by pumping 
					  messages to this function. Create new
					  thread for the OpelGL to use?
			*/

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

					WIN32_ASSERT();

					return 0;
				}
				case WM_SIZE:
					// Get new size of the window.
					RECT wndRect;

					GetWindowRect(window->impl->hWnd, &wndRect);

					window->impl->cImpl.width = wndRect.right - wndRect.left;
					window->impl->cImpl.height = wndRect.bottom - wndRect.top;

					return 0;
				case WM_MOVE:
					GetWindowRect(window->impl->hWnd, &wndRect);

					window->impl->cImpl.x = wndRect.left;
					window->impl->cImpl.y = wndRect.top;

					return 0;
			}

			// Handle any messages the switch statement didn't.
			return DefWindowProc(hWnd, message, wParam, lParam);
		}

		// Public.

		HWND Window::getHandle() const {
			assert(impl->cImpl.initialized);

			return impl->hWnd;
		}

		String Window::getTitle() const {
			return impl->cImpl.title;
		}
		void Window::setTitle(const String& title) {
			const std::wstring stemp = std::wstring(title.begin(), title.end());

			impl->lpcwTitle = stemp.c_str();
			impl->cImpl.title = title;

			if (impl->cImpl.initialized) {
				SetWindowText(impl->hWnd, impl->lpcwTitle);
			}
		}

		void Window::minimize() {
			assert(impl->cImpl.initialized);

			if (impl->cImpl.isMinimized) return;

			ShowWindow(impl->hWnd, SW_MINIMIZE);
			
			impl->cImpl.isMinimized = true;
		}
		void Window::show() {
			assert(impl->cImpl.initialized);

			if (impl->cImpl.isMinimized) {
				ShowWindow(impl->hWnd, SW_RESTORE);

				impl->cImpl.isMinimized = false;
			}
			else {
				ShowWindow(impl->hWnd, SW_SHOW);
			}
		}

		void Window::setSize(const int32 width, const int32 height) {
			if (impl->cImpl.initialized) MoveWindow(impl->hWnd, impl->cImpl.x, impl->cImpl.y, width, height, TRUE);
			else {
				impl->cImpl.width = width;
				impl->cImpl.height = height;
			}
		}
		void Window::setWidth(const int32 width) {
			if (impl->cImpl.initialized) MoveWindow(impl->hWnd, impl->x, impl->y, width, impl->cImpl.height, TRUE);
			else {
				impl->cImpl.width = width;
			}
		}
		void Window::setHeight(const int32 height) {
			if (impl->cImpl.initialized) MoveWindow(impl->hWnd, impl->cImpl.x, impl->cImpl.y, impl->cImpl.width, height, TRUE);
			else {
				impl->cImpl.height = height;
			}
		}

		void Window::setPosition(const int32 x, const int32 y) {
			if (impl->cImpl.initialized) MoveWindow(impl->hWnd, y, x, impl->cImpl.width, impl->cImpl.height, TRUE);
			else {
				impl->cImpl.x = x;
				impl->cImpl.y = y;
			}
		}
		void Window::setX(const int32 x) {
			if (impl->cImpl.initialized) MoveWindow(impl->hWnd, x, impl->cImpl.y, impl->cImpl.width, impl->cImpl.height, TRUE);
			else {
				impl->cImpl.x = x;
			}
		}
		void Window::setY(const int32 y) {
			if (impl->cImpl.initialized) MoveWindow(impl->hWnd, impl->cImpl.x, y, impl->cImpl.width, impl->cImpl.height, TRUE);
			else {
				impl->cImpl.y = y;
			}
		}

		int32 Window::getX() const {
			return impl->cImpl.x;
		}
		int32 Window::getY() const {
			return impl->cImpl.y;
		}

		uint32 Window::getClientWidth() const {
			assert(impl->cImpl.initialized);

			RECT clntRect;

			GetClientRect(impl->hWnd, &clntRect);

			return clntRect.right- clntRect.left;
		}
		uint32 Window::getClientHeight() const {
			assert(impl->cImpl.initialized);

			RECT clntRect;

			GetClientRect(impl->hWnd, &clntRect);

			return clntRect.bottom - clntRect.top;
		}

		inline int32 Window::getWidth() {
			return impl->cImpl.width;
		}
		inline int32 Window::getHeight() {
			return impl->cImpl.height;
		}

		void Window::listen() const {
			assert(impl->cImpl.initialized);

			MSG msg;

			if (PeekMessage(&msg, NULL, 0, 0, PM_REMOVE)) {
				// translate keystroke messages into the right format
				TranslateMessage(&msg);

				// send the message to the WindowProc function
				DispatchMessage(&msg);

				impl->cImpl.isWindowOpen = msg.message != WM_QUIT;
			}
		}

		bool Window::isOpen() const {
			assert(impl->cImpl.initialized);

			return impl->cImpl.isWindowOpen;
		}

		void Window::close() {
			assert(impl->cImpl.initialized);

			if (!impl->cImpl.isWindowOpen) return;

			impl->cImpl.isWindowOpen = false;
		}

		bool Window::initialize() {
			assert(!impl->cImpl.initialized);

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
										impl->lpcwTitle,
										WS_OVERLAPPEDWINDOW,
										impl->cImpl.x,
										impl->cImpl.y,
										impl->cImpl.width,
										impl->cImpl.height,
										NULL,
										NULL,
										impl->hInstance,
										this);

			WIN32_REQUIRE(impl->hWnd, L"failed to create window");

			// Set background to black.
			const HBRUSH brush = CreateSolidBrush(RGB(0, 0, 0));
			SetClassLongPtr(impl->hWnd, GCLP_HBRBACKGROUND, (LONG)brush);

			impl->cImpl.initialized = true;
			impl->cImpl.isWindowOpen = true;

			// Return results.
			return impl->cImpl.initialized;
		}

		Window::~Window() {
			delete impl;
		}
	}
}

#endif