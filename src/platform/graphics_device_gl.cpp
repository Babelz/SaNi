#include "sani/platform/graphics_device.hpp"
#include "sani/platform/viewport.hpp"
#include "sani/platform/color.hpp"

// Contains WindowsGL and LinuxGL implementations of the graphics device.

#if SANI_TARGET_PLATFORM == SANI_PLATFORM_WIN32

		// Win32 OpenGL implementation.

#include "GL/glew.h"

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

			// Used to store the desktop location of the window
			// when we are toggling fullscreen.
			uint32 windowedLocationX;
			uint32 windowedLocationY;

			Impl() : renderingContext(NULL),
					 deviceContext(NULL),
					 hWnd(NULL),
					 hInstance(NULL),
					 fullscreen(false),
					 windowedLocationX(0),
					 windowedLocationY(0) {
			}
		};

		GraphicsDevice::GraphicsDevice(const HWND hWnd, const HINSTANCE hInstance) : impl(new Impl())  {
			impl->hWnd = hWnd;
			impl->hInstance = hInstance;
			impl->deviceContext = GetDC(hWnd);
		}

		void GraphicsDevice::checkForErrors() {
			// Platform size assertion.
			static_assert(sizeof(GLuint) == sizeof(uint32), "sizeof(GLuint) != sizeof(uint32)");

			GLuint error = 0;

			// Get all OpenGL errors.
			while ((error = glGetError()) != 0) {
				errorBuffer.push(static_cast<uint32>(error));
			}
		}

		bool GraphicsDevice::isFullscreen() const {
			return impl->fullscreen;
		}
		void GraphicsDevice::setFullscreen() {
			// Just do the toggling here. Does it really matter?
			// I think that this should be done by the window class
			// but does it really matter? I pref that the
			// window only holds state data and some basic functionalities.
			
			// Get window rect.
			RECT wndRect;
			GetWindowRect(impl->hWnd, &wndRect);

			// Store the location of the window.
			impl->windowedLocationX = wndRect.left;
			impl->windowedLocationY = wndRect.top;
			
			// Set style to fullscreen.
			SetWindowLongPtr(impl->hWnd, GWL_STYLE, WS_SYSMENU | WS_POPUP | WS_CLIPCHILDREN | WS_VISIBLE);

			// Compute size of the window and move it.
			// This is required for it to go in to
			// fullscreen mode.
			const uint32 width = wndRect.right - wndRect.left;
			const uint32 height = wndRect.bottom - wndRect.top;

			MoveWindow(impl->hWnd, 0, 0, width, height, TRUE);
		}
		void GraphicsDevice::setWindowed() {
			RECT wndRect;
			RECT rect;

			GetWindowRect(impl->hWnd, &wndRect);

			const uint32 width = wndRect.right - wndRect.left;
			const uint32 height = wndRect.bottom - wndRect.top;
		
			rect.left = impl->windowedLocationX;
			rect.top = impl->windowedLocationY;
			rect.bottom = height;
			rect.right = width;

			SetWindowLongPtr(impl->hWnd, GWL_STYLE, WS_OVERLAPPEDWINDOW | WS_VISIBLE);
			AdjustWindowRect(&rect, WS_OVERLAPPEDWINDOW, FALSE);
			MoveWindow(impl->hWnd, impl->windowedLocationX, impl->windowedLocationY, width, height, TRUE);
		}

		bool GraphicsDevice::hasErrors() const {
			return !errorBuffer.empty();
		}
		uint32 GraphicsDevice::getError() {
			assert(hasErrors());

			const uint32 nextError = errorBuffer.top();
			
			errorBuffer.pop();
		
			return nextError;
		}

		void GraphicsDevice::setViewport(const Viewport& viewport) {
			impl->viewport = viewport;

			glViewport(impl->viewport.x, impl->viewport.y, impl->viewport.width, impl->viewport.height);
		
			checkForErrors();
		}
		const Viewport& GraphicsDevice::getViewport() const {
			return impl->viewport;
		}

		bool GraphicsDevice::initialize() {
			// Create OpenGL context.
			// No need to set the pixel format as the window should 
			// have done it already.

			// Check for pre-init errors.
			checkForErrors();
			
			if (hasErrors()) return false;

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
			
			// Post-init error checks.
			checkForErrors();

			if (hasErrors()) {
				// Clean up before returning.
				cleanUp();

				return false;
			}

			// No errors, init ok.
			return true;
		}
		bool GraphicsDevice::cleanUp() {
			// Swap context and delete it.
			wglMakeCurrent(impl->deviceContext, NULL);
			wglDeleteContext(impl->renderingContext);
			
			// Check for OpenGL errors.
			checkForErrors();

			// Check for windows errors.
			DWORD error = GetLastError();

			if (error != 0) errorBuffer.push(static_cast<uint32>(error));

			return hasErrors();
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

			checkForErrors();
		}
		void GraphicsDevice::present() {
			// TODO: present shit (buffers) etc?
			SwapBuffers(impl->deviceContext);

			checkForErrors();
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

