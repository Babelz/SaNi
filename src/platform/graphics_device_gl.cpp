#include "sani/platform/graphics_device.hpp"
#include "sani/platform/viewport.hpp"
#include "sani/platform/color.hpp"

// Contains WindowsGL and LinuxGL implementations of the graphics device.

/*
	TODO: when creating other implementations, refactor the implementatio class and
		  the device class as some fields and functions are common accross 
		  implementations and APIs.
*/

#if SANI_TARGET_PLATFORM == SANI_PLATFORM_WIN32

		// Win32 OpenGL implementation.

#include "sani/platform/render_target_2d.h"
#include "GL/wglew.h"
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

			// Should the adapter be working in fullscreen mode.
			bool fullscreen;

			// Color used to clear the screen and
			// converted float values.
			Color color;
			float cR;
			float cG;
			float cB;
			float cA;

			// Used to store the desktop location of the window
			// when we are toggling fullscreen.
			// We could also store the size information aswell
			// but the user can resize the window or the resolution
			// and thus the state information contained here
			// would overwrite it.
			uint32 windowedLocationX;
			uint32 windowedLocationY;

			uint32 backBufferWidth;
			uint32 backBufferHeight;

			// Default backbuffer of the device.
			// Everything gets drawn this.
			RenderTarget2D* defaultRenderTarget;
			RenderTarget2D* currentRenderTarget;

			Viewport viewport;

			Impl() : renderingContext(NULL),
					 deviceContext(NULL),
					 hWnd(NULL),
					 hInstance(NULL),
					 fullscreen(false),
					 windowedLocationX(0),
					 windowedLocationY(0),
					 backBufferWidth(0),
					 backBufferHeight(0),
					 defaultRenderTarget(nullptr),
					 currentRenderTarget(nullptr) {
			}

			~Impl() {
				delete defaultRenderTarget;
			}
		};

		GraphicsDevice::GraphicsDevice(const HWND hWnd, const HINSTANCE hInstance, const int32 backBufferWidth, const int32 backBufferHeight) : impl(new Impl())  {
			impl->hWnd = hWnd;
			impl->hInstance = hInstance;
			impl->deviceContext = GetDC(hWnd);
			impl->backBufferWidth = backBufferWidth;
			impl->backBufferHeight = backBufferHeight;
			impl->viewport = Viewport(0, 0, impl->backBufferWidth, impl->backBufferHeight);
		}

		void GraphicsDevice::checkForErrors() {
			GLint error = 0;

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

		uint32 GraphicsDevice::getBackBufferWidth() const {
			return impl->backBufferWidth;
		}
		uint32 GraphicsDevice::getBackBufferHeight() const {
			return impl->backBufferHeight;
		}

		void GraphicsDevice::setBackBufferWidth(const uint32 newWidth) {
			impl->backBufferWidth = newWidth;
		}
		void GraphicsDevice::setBackBufferHeight(const uint32 newHeight) {
			impl->backBufferHeight = newHeight;
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

			GLenum state = glewInit();

			if (state != GLEW_OK) {
				// 1282 invalid operation.
				// TODO: translate to some human readable error messages.
				errorBuffer.push(1282);
			}

			// TODO: use 3.3 always or just get the newest supported version?
			// TODO: select OpenGL version to use.
			/*GLint initAttribs[] = 
			{
				WGL_CONTEXT_MAJOR_VERSION_ARB, 3,
				WGL_CONTEXT_MINOR_VERSION_ARB, 3,

				// Uncomment this for forward compatibility mode
				//WGL_CONTEXT_FLAGS_ARB, WGL_CONTEXT_FORWARD_COMPATIBLE_BIT_ARB,
				// Uncomment this for Compatibility profile
				//WGL_CONTEXT_PROFILE_MASK_ARB, WGL_CONTEXT_COMPATIBILITY_PROFILE_BIT_ARB,

				WGL_CONTEXT_PROFILE_MASK_ARB, WGL_CONTEXT_CORE_PROFILE_BIT_ARB,
				0
			};

			// Try set the attribs spec version of the context. Fallback to the first one if this
			// one fails.
			HGLRC compHRC = wglCreateContextAttribsARB(impl->deviceContext, 0, initAttribs);
			if (compHRC && wglMakeCurrent(impl->deviceContext, compHRC)) impl->renderingContext = compHRC;
			*/

			// Check for pre-init errors.
			checkForErrors(); if (hasErrors()) return false;

			// Enable GL settings.
			glEnable(GL_DEPTH_TEST);
			glEnable(GL_ALPHA_TEST);
			glEnable(GL_BLEND);

			checkForErrors(); if (hasErrors()) return false;

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

		bool GraphicsDevice::applyChanges() {
			glViewport(impl->viewport.x, impl->viewport.y, impl->viewport.width, impl->viewport.height);

			// Check for errors.
			checkForErrors();
			if (hasErrors()) return false;
		
			return true;
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

		void GraphicsDevice::setRenderTarget(RenderTarget2D* renderTarget) {
			if (renderTarget == nullptr) impl->currentRenderTarget = impl->defaultRenderTarget;
			else						 impl->currentRenderTarget = renderTarget;
		}

		void GraphicsDevice::generateTexture(RenderTexture& texture, const uint32 width, const uint32 height) {
			GLuint glTexture = 0;

			// Generate the texture.
			glGenTextures(1, &glTexture);
			glBindTexture(GL_TEXTURE_2D, glTexture);
			
			glTexImage2D(GL_TEXTURE_2D,
				0,
				GL_RGBA,
				width,
				height,
				0,
				GL_RGBA,
				GL_UNSIGNED_BYTE,
				0);

			glTextureParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);
			glTextureParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
		
			glBindTexture(GL_TEXTURE_2D, 0);

			checkForErrors();

			texture = static_cast<RenderTexture>(glTexture);
		}	
		void GraphicsDevice::generateRenderTarget2D(RenderTexture& texture, Buffer& frameBuffer, Buffer& colorBuffer, Buffer& depthBuffer, const uint32 width, const uint32 height) {
			// Assume that the render texture has been initialized and generated.
			
			// Generate frame buffer.
			GLuint glFrameBuffer = 0;
			glGenFramebuffers(1, &glFrameBuffer);
			glBindFramebuffer(GL_FRAMEBUFFER, glFrameBuffer);

			// Check for errors.
			checkForErrors(); if (hasErrors()) return;

			// Assume the texture is generated and in a valid state.
			GLuint glTexture = static_cast<GLuint>(texture);
			glBindTexture(GL_TEXTURE_2D, glTexture);

			checkForErrors(); if (hasErrors()) return;
		
			// Generate depth buffer.
			GLuint glDepthBuffer = 0;
			glGenRenderbuffers(1, &glDepthBuffer);
			glBindRenderbuffer(GL_RENDERBUFFER, glDepthBuffer);
			glRenderbufferStorage(GL_RENDERBUFFER, GL_DEPTH_COMPONENT, width, height);
			glFramebufferRenderbuffer(GL_FRAMEBUFFER, GL_DEPTH_ATTACHMENT, GL_RENDERBUFFER, glDepthBuffer);
			
			checkForErrors(); if (hasErrors()) return;

			// Set as attachement#0?
			glFramebufferTexture(GL_FRAMEBUFFER, GL_COLOR_ATTACHMENT0, glTexture, 0);

			glBindRenderbuffer(GL_RENDERBUFFER, 0);
			glBindTexture(GL_TEXTURE_2D, 0);
			glBindFramebuffer(GL_FRAMEBUFFER, 0);
			
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

