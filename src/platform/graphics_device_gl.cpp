#include "sani/platform/render_target_2d.hpp"
#include "sani/platform/graphics_device.hpp"
#include "sani/platform/viewport.hpp"
#include "sani/platform/color.hpp"
#include <sstream>

// Contains WindowsGL and LinuxGL implementations of the graphics device.

/*
	TODO: when creating other implementations, refactor the implementatio class and
		  the device class as some fields and functions are common accross 
		  implementations and APIs.
*/

namespace sani {
	namespace graphics {

		class GraphicsDevice::Cimpl {
		public:
			uint32 backBufferWidth;
			uint32 backBufferHeight;

			// Default backbuffer of the device.
			// Everything gets drawn this.
			RenderTarget2D* defaultRenderTarget;
			RenderTarget2D* currentRenderTarget;

			Viewport viewport;

			Cimpl() : backBufferWidth(0),
					  backBufferHeight(0),
					  defaultRenderTarget(nullptr),
					  currentRenderTarget(nullptr) {
			}

			~Cimpl() {
				delete defaultRenderTarget;
			}
		};
	}
}

#if SANI_TARGET_PLATFORM == SANI_PLATFORM_WIN32

#include "GL/wglew.h"
#include "GL/glew.h"

// Win32 impl.
namespace sani {
	namespace graphics {

		// Private Win32GL Impl class.
		class GraphicsDevice::Impl {
		public:
			// Used to store the desktop location of the window
			// when we are toggling fullscreen.
			// We could also store the size information aswell
			// but the user can resize the window or the resolution
			// and thus the state information contained here
			// would overwrite it.
			uint32 windowedLocationX;
			uint32 windowedLocationY;

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

			// Common impl.
			Cimpl cImpl;

			Impl() : renderingContext(NULL),
				deviceContext(NULL),
				hWnd(NULL),
				hInstance(NULL),
				fullscreen(false),
				windowedLocationX(0),
				windowedLocationY(0) {
			}
		};

		GraphicsDevice::GraphicsDevice(const HWND hWnd, const HINSTANCE hInstance, const int32 backBufferWidth, const int32 backBufferHeight) : impl(new Impl())  {
			impl->hWnd = hWnd;
			impl->hInstance = hInstance;
			impl->deviceContext = GetDC(hWnd);
			impl->cImpl.backBufferWidth = backBufferWidth;
			impl->cImpl.backBufferHeight = backBufferHeight;
			impl->cImpl.viewport = Viewport(0, 0, impl->cImpl.backBufferWidth, impl->cImpl.backBufferHeight);
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

			// Get current monitors size.
			const uint32 width = GetSystemMetrics(SM_CXSCREEN);
			const uint32 height = GetSystemMetrics(SM_CYSCREEN);

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
				errorBuffer.push(GRAPHICS_ERROR(1282));
			}

#pragma region OpenGL version selection
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
#pragma endregion

			// Check for pre-init errors.
			CHECK_FOR_ERRORS(); if (hasErrors()) return false;

			// Enable GL settings.
			glEnable(GL_DEPTH_TEST);
			glEnable(GL_ALPHA_TEST);
			glEnable(GL_BLEND);

			CHECK_FOR_ERRORS(); if (hasErrors()) return false;

			glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);

			// Set the window full screen. Default is windowed.
			if (impl->fullscreen) setFullscreen();

			// Create default viewport if user has not given us one.
			if (impl->cImpl.viewport.isDefault()) {
				RECT clntRect;

				GetClientRect(impl->hWnd, &clntRect);

				impl->cImpl.viewport = Viewport(0, 0, clntRect.right - clntRect.left, clntRect.bottom - clntRect.top);
			}

			// Set viewport.
			glViewport(impl->cImpl.viewport.x, impl->cImpl.viewport.y, impl->cImpl.viewport.width, impl->cImpl.viewport.height);

			// Post-init error checks.
			CHECK_FOR_ERRORS();

			if (hasErrors()) {
				// Clean up before returning.
				cleanUp();

				return false;
			}

			// No errors, init ok.
			return true;
		}
		bool GraphicsDevice::cleanUp() {
			CHECK_FOR_ERRORS();

			// Swap context and delete it.
			wglDeleteContext(impl->renderingContext);
			wglMakeCurrent(impl->deviceContext, NULL);

			// Check for windows errors.
			DWORD error = GetLastError();

			return hasErrors();
		}

		void GraphicsDevice::clear(const Color& color) {
			SwapBuffers(impl->deviceContext);

			// Change clear color for the GL.
			glClearColor(color.r, color.g, color.b, color.a);

			glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

			CHECK_FOR_ERRORS();
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

#include <GLES2/gl2.h>
namespace sani {
	namespace graphics {

		class GraphicsDevice::Impl {
		public:
			Cimpl cImpl;
		};
	}
}

#endif

#if SANI_TARGET_PLATFORM == SANI_PLATFORM_IOS

		// iOS OpenGLES implementation.

#endif

// Common impl of the graphics device.
namespace sani {
	namespace graphics {

		void GraphicsDevice::checkForErrors(const char* func, const int32 line) {
			GLint error = 0;

			// Get all OpenGL errors.
			while ((error = glGetError()) != 0) {
				errorBuffer.push(GraphicsError(error, func, line));
			}
		}

		uint32 GraphicsDevice::getBackBufferWidth() const {
			return impl->cImpl.backBufferWidth;
		}
		uint32 GraphicsDevice::getBackBufferHeight() const {
			return impl->cImpl.backBufferHeight;
		}

		void GraphicsDevice::setBackBufferWidth(const uint32 newWidth) {
			impl->cImpl.backBufferWidth = newWidth;
		}
		void GraphicsDevice::setBackBufferHeight(const uint32 newHeight) {
			impl->cImpl.backBufferHeight = newHeight;
		}

		bool GraphicsDevice::hasErrors() const {
			return !errorBuffer.empty();
		}
		GraphicsError GraphicsDevice::getError() {
			assert(hasErrors());

			const GraphicsError nextError = errorBuffer.top();

			errorBuffer.pop();

			return nextError;
		}

		void GraphicsDevice::setViewport(const Viewport& viewport) {
			impl->cImpl.viewport = viewport;

			glViewport(impl->cImpl.viewport.x, impl->cImpl.viewport.y, impl->cImpl.viewport.width, impl->cImpl.viewport.height);

			// Check for errors.
			CHECK_FOR_ERRORS();
		}
		const Viewport& GraphicsDevice::getViewport() const {
			return impl->cImpl.viewport;
		}

		void GraphicsDevice::bindTexture(const RenderTexture texture) {
			const GLuint glTexture = static_cast<GLuint>(texture);

			glBindTexture(GL_TEXTURE_2D, glTexture);
		}
		void GraphicsDevice::unbindTexture() {
			glBindTexture(GL_TEXTURE_2D, 0);
		}

		void GraphicsDevice::setRenderTarget(RenderTarget2D* renderTarget) {
			if (renderTarget == nullptr) impl->cImpl.currentRenderTarget = impl->cImpl.defaultRenderTarget;
			else						 impl->cImpl.currentRenderTarget = renderTarget;

			glBindFramebuffer(GL_FRAMEBUFFER, static_cast<GLuint>(impl->cImpl.currentRenderTarget->getFramebuffer()));

			/*
			http://www.opengl-tutorial.org/intermediate-tutorials/tutorial-14-render-to-texture/

			The fragment shader just needs a minor adaptation:

			Inside the fragment shader
			layout(location = 0) out vec3 color;

			This means that when writing in the variable “color”,
			we will actually write in the Render Target 0,
			which happens to be our texure because DrawBuffers[0] is GL_COLOR_ATTACHMENTi,
			which is, in our case, renderedTexture.
			*/
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

#if SANI_TARGET_PLATFORM != SANI_PLATFORM_ANDROID
			glTextureParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);
			glTextureParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
#elif SANI_TARGET_PLATFORM == SANI_PLATFORM_ANDROID
			glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);
			glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
#endif

			glBindTexture(GL_TEXTURE_2D, 0);

			CHECK_FOR_ERRORS();

			texture = static_cast<RenderTexture>(glTexture);
		}
		void GraphicsDevice::generateRenderTarget2D(RenderTexture& texture, Buffer& frameBuffer, Buffer& colorBuffer, Buffer& depthBuffer, const uint32 width, const uint32 height) {
			// Assume that the render texture has been initialized and generated.

			// Generate frame buffer.
			GLuint glFrameBuffer = 0;
			glGenFramebuffers(1, &glFrameBuffer);
			glBindFramebuffer(GL_FRAMEBUFFER, glFrameBuffer);

			// Check for errors.
			CHECK_FOR_ERRORS(); if (hasErrors()) return;

			// Assume the texture is generated and in a valid state.
			GLuint glTexture = static_cast<GLuint>(texture);
			glBindTexture(GL_TEXTURE_2D, glTexture);

			CHECK_FOR_ERRORS(); if (hasErrors()) return;

			// Generate depth buffer.
			GLuint glDepthBuffer = 0;
			glGenRenderbuffers(1, &glDepthBuffer);
			glBindRenderbuffer(GL_RENDERBUFFER, glDepthBuffer);
			glRenderbufferStorage(GL_RENDERBUFFER, GL_DEPTH_COMPONENT, width, height);
			glFramebufferRenderbuffer(GL_FRAMEBUFFER, GL_DEPTH_ATTACHMENT, GL_RENDERBUFFER, glDepthBuffer);

			CHECK_FOR_ERRORS(); if (hasErrors()) return;

#if SANI_TARGET_PLATFORM != SANI_PLATFORM_WIN32
			// Set as attachement#0?
			glFramebufferTexture(GL_FRAMEBUFFER, GL_COLOR_ATTACHMENT0, glTexture, 0);
#elif SANI_TARGET_PLATFORM == SANI_PLATFORM_ANDROID 
			glFramebufferTexture2D(GL_FRAME_BUFFER, GL_COLOR_ATTACHMENT0, GL_TEXTURE2D, glTexture, 0);
#endif

			glBindRenderbuffer(GL_RENDERBUFFER, 0);
			glBindTexture(GL_TEXTURE_2D, 0);
			glBindFramebuffer(GL_FRAMEBUFFER, 0);

			CHECK_FOR_ERRORS();
		}

		void GraphicsDevice::compileShader(Shader& shader, const char* source, const ShaderType type) {
			GLint result = GL_FALSE;
			GLuint glShader = 0;

			switch (type) {
			case ShaderType::Vertex:
				glShader = glCreateShader(GL_VERTEX_SHADER);
				break;
			case ShaderType::Pixel:
				glShader = glCreateShader(GL_FRAGMENT_SHADER);
				break;
			default:
				throw std::logic_error("At GraphicsDevice::compileShader - unsupported or invalid shader type");
			}

			glShaderSource(glShader, 1, &source, nullptr);
			glCompileShader(glShader);
			glGetShaderiv(glShader, GL_COMPILE_STATUS, &result);

			CHECK_FOR_ERRORS();

			// Push custom error code.
			if (result != GL_TRUE) errorBuffer.push(CUSTOM_GRAPHICS_ERROR("Failed to compile shader"));
		}
		void GraphicsDevice::deleteShader(const Shader shader) {
			const GLuint glShader = static_cast<GLuint>(shader);

			glDeleteShader(glShader);

			CHECK_FOR_ERRORS();
		}

		void GraphicsDevice::createProgram(ShaderProgram& program) {
			GLuint glProgram = glCreateProgram();

			CHECK_FOR_ERRORS();

			if (glProgram == 0) {
				errorBuffer.push(CUSTOM_GRAPHICS_ERROR("Could not create shader program"));

				return;
			}

			program = static_cast<ShaderProgram>(glProgram);
		}
		void GraphicsDevice::linkToProgram(const ShaderProgram program, const Shader shader, const bool dispose) {
			glAttachShader(program, shader);

			if (dispose) deleteShader(shader);

			CHECK_FOR_ERRORS();
		}
		void GraphicsDevice::linkProgram(const ShaderProgram program) {
			glLinkProgram(program);

			GLint result = 0;

			glGetProgramiv(program, GL_LINK_STATUS, &result);

			CHECK_FOR_ERRORS();

			if (result != GL_TRUE) errorBuffer.push(CUSTOM_GRAPHICS_ERROR("Failed to link shader to a program"));
		}

		void GraphicsDevice::useProgram(const ShaderProgram program) {
			glUseProgram(program);

			CHECK_FOR_ERRORS();
		}

		void GraphicsDevice::setShaderUniform(const ShaderProgram shader, const char* name, void* data, const UniformType type) {
			GLint uniformLocation = glGetUniformLocation(shader, name);

			// Uniform not found.
			if (uniformLocation == -1) {
				CHECK_FOR_ERRORS();

				std::stringstream ss;

				ss << "Invalid uniform name, uniform not found. Name was \"";
				ss << name;
				ss << "\"";

				errorBuffer.push(CUSTOM_GRAPHICS_ERROR(ss.get()));

				return;
			}

			/*
			TODO: is this just fine? support all needed uniforms an not all of them.
			*/

			// Set the uniform value.
			switch (type) {
			case Mat4F:
				glUniformMatrix4fv(uniformLocation, 1, GL_FALSE, static_cast<GLfloat*>(data));
				break;
			case Mat3F:
				glUniformMatrix3fv(uniformLocation, 1, GL_FALSE, static_cast<GLfloat*>(data));
				break;
			default:
				throw std::logic_error("Invalid or unsupported uniform type");
			}
		}

		GraphicsDevice::~GraphicsDevice() {
			delete impl;
		}
	}
}

