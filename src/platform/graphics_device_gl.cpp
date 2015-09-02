#include "sani/platform/graphics_device.hpp"
#include "sani/platform/viewport.hpp"
#include "sani/platform/color.hpp"

// Contains WindowsGL and LinuxGL implementations of the graphics device.

#if SANI_TARGET_PLATFORM == SANI_PLATFORM_WIN32

		// Win32 OpenGL implementation.

#include "GL/glew.h"
#include "GL/GL.h"

namespace sani {
	namespace graphics {

		/*
			TODO: implement fullscreen and windowed modes
				  implement OpenGL error handling 
		*/
		
		// Private Win32GL Impl class.
		class GraphicsDevice::Impl {
		public:
			// Permanent rendering context.
			HGLRC renderingContext;
			// Private HDI device context.
			HDC deviceContext;

			// Window handle.
			HWND hWnd;
			// Application handle.
			HINSTANCE hInstance;

			Viewport viewport;
			
			// Color used to clear the screen and
			// converted float values.
			Color color;
			float cR;
			float cG;
			float cB;
			float cA;

			// Should the adapter be working in fullscreen mode.
			bool fullscreen;

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

		bool GraphicsDevice::isFullscreen() const {
			return impl->fullscreen;
		}
		void GraphicsDevice::setFullscreen() {
			// TODO: toggle fullscreen.
		}
		void GraphicsDevice::setWindowed() {
			// TODO: toggle windowed mode.
		}

		bool GraphicsDevice::hasErrors() const {
			// TODO: implement.
			return false;
		}
		uint8 GraphicsDevice::getError() const {
			// TODO: return next error from error buffer.
			return 0;
		}

		void GraphicsDevice::setViewport(const Viewport& viewport) {
			impl->viewport = viewport;

			glViewport(impl->viewport.x, impl->viewport.y, impl->viewport.width, impl->viewport.height);
		}
		const Viewport& GraphicsDevice::getViewport() const {
			return impl->viewport;
		}

		bool GraphicsDevice::initialize() {
			// Create OpenGL context.
			// No need to set the pixel format as the window should 
			// have done it already.

			// Create context and set it active.
			// TODO: add error handling to init and context creation.
			impl->renderingContext = wglCreateContext(impl->deviceContext);
			wglMakeCurrent(impl->deviceContext, impl->renderingContext);
			
			// Enable GL settings.
			glEnable(GL_DEPTH_TEST);
			glEnable(GL_ALPHA_TEST);
			glEnable(GL_BLEND);

			glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);

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

			setViewport(impl->viewport);

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

		void GraphicsDevice::clear(const Color& color) {
			if (impl->color != color) {
				// Convert color components to floats.
				impl->color = color;
				impl->cR = color.r / 255.0f;
				impl->cG = color.g / 255.0f;
				impl->cB = color.b / 255.0f;
				impl->cA = color.a / 255.0f;
				
				// Change clear color for the GL.
				glClearColor(impl->cR, impl->cG, impl->cB, impl->cA);
			}

			glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
		}
		void GraphicsDevice::present() {
			// TODO: present shit (buffers) etc?
			SwapBuffers(impl->deviceContext);
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

