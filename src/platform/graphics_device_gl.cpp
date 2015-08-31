#include "sani/platform/platform_config.hpp"

// Contains WindowsGL and LinuxGL implementations of the graphics device.

#if SANI_TARGET_PLATFORM == SANI_PLATFORM_WIN32

		// Win32 OpenGL implementation.

#include <windows.h>
#include "sani/platform/graphics_device.hpp"
#include "GL/glew.h"
#include "GL/GL.h"
#include "GL/wglew.h"

namespace sani {
	namespace graphics {
		// Private Win32GL Impl class.
		class GraphicsDevice::Impl {
		public:
			// Permanent rendering context.
			HGLRC renderingContext;
			// Private HDI device context.
			HDC deviceContext;

			HWND hWnd;
			HINSTANCE hInstance;

			bool fullscreen;

			Viewport viewport;
		
			Impl() : renderingContext(NULL),
					 deviceContext(NULL),
					 hWnd(NULL),
					 hInstance(NULL),
					 fullscreen(false) {
			}
		};

		GraphicsDevice::GraphicsDevice(const HWND hWnd, const HINSTANCE hInstance) : impl(new Impl())  {
			impl->hWnd = hWnd;
			impl->hInstance = hInstance;
			impl->deviceContext = GetDC(hWnd);
		}

		bool GraphicsDevice::initialize() {
			// Create OpenGL context.
			// No need to set the pixel format as the window should 
			// have done it already.

			// Create context and set it active.
			// TODO: add error handling to init and context creation.
			impl->renderingContext = wglCreateContext(impl->deviceContext);
			wglMakeCurrent(impl->deviceContext, impl->renderingContext);
			
			// Set the window full screen. Default is windowed.
			if (impl->fullscreen) setFullscreen();

			// Create default viewport if user has not given us one.
			if (impl->viewport.isDefault()) {
				RECT clntRect;
				
				GetClientRect(impl->hWnd, &clntRect);
				
				impl->viewport = Viewport(0, 0, clntRect.right - clntRect.left, clntRect.bottom - clntRect.top);
			}

			// Set viewport.
			glViewport(impl->viewport.x, impl->viewport.y, impl->viewport.width, impl->viewport.height);

			// TODO: add error handling.
			return true;
		}
		bool GraphicsDevice::cleanUp() {
			// Swap context and delete it.
			wglMakeCurrent(impl->deviceContext, NULL);
			wglDeleteContext(impl->renderingContext);

			DWORD error = GetLastError();

			// If error equals zero, there are no errors.
			return error == 0;
		}

		GraphicsDevice::~GraphicsDevice() {
			delete impl;
		}
	}
}

#endif

#if SANI_TARGET_PLATFORM == SANI_PLATFORM_LINUX

		// Linux OpenGL implementation.

#endif

		// Contains Android GLES and iOS GLES implementations of the graphics device.

#if SANI_TARGET_PLATFORM == SANI_PLATFORM_ANDROID

		// Android OpenGLES implementation.

#endif

#if SANI_TARGET_PLATFORM == SANI_PLATFORM_IOS

		// iOS OpenGLES implementation.

#endif

