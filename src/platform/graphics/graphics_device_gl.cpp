#include "sani/platform/graphics/render_target_2d.hpp"
#include "sani/platform/graphics/graphics_device.hpp"
#include "sani/platform/graphics/viewport.hpp"
#include "sani/debug.hpp"
#include <sstream>
#include <stdexcept>

// Contains WindowsGL and LinuxGL implementations of the graphics device.

/*
	TODO: when creating other implementations, refactor the implementation class and
		  the device class as some fields and functions are common across 
		  implementations and APIs.
*/

namespace sani {
	namespace graphics {

		class GraphicsDevice::Cimpl {
		public:
			uint32 backBufferWidth;
			uint32 backBufferHeight;

			// Default back buffer of the device.
			// Everything gets drawn to this.
			RenderTarget2D* backbuffer;
			RenderTarget2D* currentRenderTarget;

			Viewport viewport;

			Cimpl() : backBufferWidth(0),
					  backBufferHeight(0),
					  backbuffer(nullptr),
					  currentRenderTarget(nullptr) {
			}

			~Cimpl() {
				delete backbuffer;
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
			// We could also store the size information as well
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
		}

		bool GraphicsDevice::isFullscreen() const {
			return impl->fullscreen;
		}
		void GraphicsDevice::setFullscreen() {
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
			glEnable(GL_BLEND);

			CHECK_FOR_ERRORS(); if (hasErrors()) return false;

			glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
			
			// Set the window full screen. Default is windowed.
			if (impl->fullscreen) setFullscreen();

			// Set viewport.
			RECT clntRect;
			GetClientRect(impl->hWnd, &clntRect);

			Viewport viewport(0, 0, clntRect.right - clntRect.left, clntRect.bottom - clntRect.top);

			// Post-init error checks.
			CHECK_FOR_ERRORS();

			if (hasErrors()) {
				// Clean up before returning.
				cleanUp();

				return false;
			}

			// Initialize backbuffer.
			impl->cImpl.backbuffer = new RenderTarget2D(this, impl->cImpl.backBufferWidth, impl->cImpl.backBufferHeight);
			setRenderTarget(nullptr);

			setViewport(viewport);

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

		void GraphicsDevice::clear(const float32 r, const float32 g, const float32 b, const float32 a) {
			/*
				TODO: implement drawing from the backbuffer once some rendering can be done.
			*/

			SwapBuffers(impl->deviceContext);

			// Change clear color for the GL.
			glClearColor(r, g, b, a);

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
#include <stdexcept>
namespace sani {
	namespace graphics {

		class GraphicsDevice::Impl {
		public:
			Cimpl cImpl;
		};

		GraphicsDevice::GraphicsDevice() : impl(new Impl) {

		}

		void GraphicsDevice::clear(const float32 r, const float32 g, const float32 b, const float32 a) {
			glClearColor(r, g, b, a);

			glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

			CHECK_FOR_ERRORS();
		}
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
		void GraphicsDevice::applyBackbufferChanges() {
			const GLuint textures[] = { impl->cImpl.backbuffer->getID() };
			glDeleteTextures(1, textures);
			
			const GLuint buffers[] = { impl->cImpl.backbuffer->getFramebuffer(),
									   impl->cImpl.backbuffer->getColorBuffer(),
									   impl->cImpl.backbuffer->getDepthBuffer() };
			glDeleteBuffers(3, buffers);

			delete impl->cImpl.backbuffer;

			impl->cImpl.backbuffer = new RenderTarget2D(this, impl->cImpl.backBufferWidth, impl->cImpl.backBufferHeight);
			setRenderTarget(nullptr);

			CHECK_FOR_ERRORS();
		}

		bool GraphicsDevice::hasErrors() const {
			return !errorBuffer.empty();
		}
		GraphicsError GraphicsDevice::getError() {
			SANI_ASSERT(hasErrors());

			const GraphicsError nextError = errorBuffer.top();

			errorBuffer.pop();

			return nextError;
		}

		void GraphicsDevice::setViewport(const Viewport& viewport) {
			impl->cImpl.viewport = viewport;

			glViewport(impl->cImpl.viewport.x, impl->cImpl.viewport.y,
				       impl->cImpl.viewport.width, impl->cImpl.viewport.height);

			CHECK_FOR_ERRORS();
		}
		Viewport GraphicsDevice::getViewport() const {
			return impl->cImpl.viewport;
		}

		void GraphicsDevice::bindTexture(const uint32 texture) {
			glBindTexture(GL_TEXTURE_2D, texture);

			CHECK_FOR_ERRORS();
		}
		void GraphicsDevice::unbindTexture() {
			glBindTexture(GL_TEXTURE_2D, 0);
			
			CHECK_FOR_ERRORS();
		}

		void GraphicsDevice::setRenderTarget(RenderTarget2D* renderTarget) {
			if (renderTarget == nullptr) impl->cImpl.currentRenderTarget = impl->cImpl.backbuffer;
			else						 impl->cImpl.currentRenderTarget = renderTarget;

			glBindFramebuffer(GL_FRAMEBUFFER, impl->cImpl.currentRenderTarget->getFramebuffer());

			/*

				http://www.opengl-tutorial.org/intermediate-tutorials/tutorial-14-render-to-texture/

				The fragment shader just needs a minor adaptation:

				Inside the fragment shader
				layout(location = 0) out vec3 color;

				This means that when writing in the variable “color”,
				we will actually write in the Render Target 0,
				which happens to be our texture because DrawBuffers[0] is GL_COLOR_ATTACHMENTi,
				which is, in our case, renderedTexture.

			*/

			CHECK_FOR_ERRORS();
		}

		int32 GraphicsDevice::surfaceFormatToOpenGl(const SurfaceFormat fmt) {
			// TODO when theres more move this elsewhere maybe?
			GLint glFormat = 0;
			switch (fmt)
			{
			case SurfaceFormat::ColorRGBA:
				glFormat = GL_RGBA;
				break;
			default:
				throw std::runtime_error("not supported format");
			}
			return glFormat;
		}

		void GraphicsDevice::generateTexture(uint32& texture, const TextureDescription& desc) {
			// generate the texture because DX wants it too..
			glGenTextures(1, &texture);
			glBindTexture(GL_TEXTURE_2D, texture);

			GLint glFormat = GraphicsDevice::surfaceFormatToOpenGl(desc.format);
			setTextureData(
				TextureTarget::Texture2D,
				0,
				desc.format,
				desc.width,
				desc.height,
				desc.format,
				nullptr);
			glBindTexture(GL_TEXTURE_2D, 0);

			CHECK_FOR_ERRORS();
		}

		void GraphicsDevice::setTextureParameter(const TextureTarget target, const TextureParameterName field, int value) {
			glTexParameteri(static_cast<GLuint>(target), static_cast<GLuint>(field), value);
		}

		void GraphicsDevice::setTextureData(const TextureTarget target, const int level, const SurfaceFormat internalFormat,
			const int width, const int height, const SurfaceFormat format, const unsigned char* data) {

			GLint glformat = surfaceFormatToOpenGl(format);
			GLint internalGlformat = surfaceFormatToOpenGl(format);
			glTexImage2D(
				static_cast<GLenum>(target),
				level,
				internalGlformat,
				width,
				height,
				0,
				glformat,
				GL_UNSIGNED_BYTE,
				data
				);
		}

		void GraphicsDevice::getTextureData(const TextureTarget target, const int level,
			const SurfaceFormat format, unsigned char* data) {
#if SANI_TARGET_PLATFORM != SANI_PLATFORM_ANDROID
			glGetTexImage(
				static_cast<GLenum>(target),
				level,
				surfaceFormatToOpenGl(format),
				GL_UNSIGNED_BYTE,
				data
				);
#else
			throw std::logic_error("not implemented");
#endif

		}

		void GraphicsDevice::generateRenderTarget2D(uint32& texture, uint32& frameBuffer, uint32& colorBuffer, uint32& depthBuffer, const uint32 width, const uint32 height) {
			// Assume that the render texture has been initialized and generated.

			/*
				TODO: impl multisampling.
			*/
#if 0
			// Generate frame buffer.
			glGenFramebuffers(1, &frameBuffer);
			glBindFramebuffer(GL_FRAMEBUFFER, frameBuffer);

			// Check for errors.
			CHECK_FOR_ERRORS(); if (hasErrors()) return;

			// Assume the texture is generated and in a valid state.
			glBindTexture(GL_TEXTURE_2D, texture);

			CHECK_FOR_ERRORS(); if (hasErrors()) return;

			// Generate depth buffer.
			glGenRenderbuffers(1, &depthBuffer);
			glBindRenderbuffer(GL_RENDERBUFFER, depthBuffer);
			glRenderbufferStorage(GL_RENDERBUFFER, GL_DEPTH_COMPONENT, width, height);
			glFramebufferRenderbuffer(GL_FRAMEBUFFER, GL_DEPTH_ATTACHMENT, GL_RENDERBUFFER, depthBuffer);

			CHECK_FOR_ERRORS(); if (hasErrors()) return;

		// WIN32	glFramebufferTexture(GL_FRAMEBUFFER, GL_COLOR_ATTACHMENT0, texture, 0);
		// ANDROID  glFramebufferTexture2D(GL_FRAMEBUFFER, GL_COLOR_ATTACHMENT0, GL_TEXTURE_2D, glTexture, 0);

			GLenum drawBuffers[1] = { GL_COLOR_ATTACHMENT0 };
			//glDrawBuffers(1, drawBuffers);

			glBindRenderbuffer(GL_RENDERBUFFER, 0);
			glBindTexture(GL_TEXTURE_2D, 0);
			glBindFramebuffer(GL_FRAMEBUFFER, 0);

			CHECK_FOR_ERRORS();
#endif
		}

		void GraphicsDevice::compileShader(uint32& shader, const char* source, const ShaderType type) {
			switch (type) {
			case ShaderType::Vertex:
				shader = glCreateShader(GL_VERTEX_SHADER);
				break;
			case ShaderType::Fragment:
				shader = glCreateShader(GL_FRAGMENT_SHADER);
				break;
			default:
				throw std::logic_error("invalid or unsupported shader type");
			}

			GLint result = 0;

			glShaderSource(shader, 1, &source, nullptr);
			glCompileShader(shader);
			glGetShaderiv(shader, GL_COMPILE_STATUS, &result);

			CHECK_FOR_ERRORS();

			// Push custom error.
			if (result != GL_TRUE) errorBuffer.push(GraphicsError("Failed to compile shader", __FUNCTION__, __LINE__));
		}
		void GraphicsDevice::deleteShader(const uint32 shader) {
			glDeleteShader(shader);

			CHECK_FOR_ERRORS();
		}

		void GraphicsDevice::createProgram(uint32& program) {
			program = glCreateProgram();

			CHECK_FOR_ERRORS();

			if (program == 0) {
				errorBuffer.push(GraphicsError("Could not create shader program", __FUNCTION__, __LINE__));

				return;
			}
		}
		void GraphicsDevice::linkToProgram(const uint32 program, const uint32 shader, const bool dispose) {
			glAttachShader(program, shader);

			if (dispose) deleteShader(shader);

			CHECK_FOR_ERRORS();
		}
		void GraphicsDevice::linkProgram(const uint32 program) {
			glLinkProgram(program);

			GLint result = 0;

			glGetProgramiv(program, GL_LINK_STATUS, &result);

			CHECK_FOR_ERRORS();

			if (result != GL_TRUE) errorBuffer.push(GraphicsError("Failed to link shader to a program", __FUNCTION__, __LINE__));
		}

		void GraphicsDevice::useProgram(const uint32 program) {
			glUseProgram(program);

			CHECK_FOR_ERRORS();
		}

		void GraphicsDevice::setShaderUniform(const uint32 shader, const char* name, void* data, const UniformType type) {
			glUseProgram(shader);

			GLint uniformLocation = glGetUniformLocation(shader, name);

			// Uniform not found.
			if (uniformLocation == -1) {
				CHECK_FOR_ERRORS();

				std::stringstream ss;

				ss << "Invalid uniform name, uniform not found. Name was \"";
				ss << name;
				ss << "\"";

				errorBuffer.push(GraphicsError(ss.get(), __FUNCTION__, __LINE__));

				return;
			}

			/*
				TODO: is this just fine? support all needed uniforms an not all of them.
			*/

			// Set the uniform value.
			switch (type) {
			case UniformType::Mat4F:
				glUniformMatrix4fv(uniformLocation, 1, GL_FALSE, reinterpret_cast<GLfloat*>(data));
				break;
			case UniformType::Mat3F:
				glUniformMatrix3fv(uniformLocation, 1, GL_FALSE, reinterpret_cast<GLfloat*>(data));
				break;
			default:
				throw std::logic_error("Invalid or unsupported uniform type");
			}

			glUseProgram(0);

			CHECK_FOR_ERRORS();
		}

		void GraphicsDevice::generateBuffer(uint32& buffer) {
			glGenBuffers(1, &buffer);

			CHECK_FOR_ERRORS();
		}
		void GraphicsDevice::bindBuffer(uint32& buffer, const BufferType type) {
			glBindBuffer(static_cast<GLenum>(type), buffer);

			CHECK_FOR_ERRORS();
		}
		void GraphicsDevice::unbindBuffer(const BufferType type) {
			glBindBuffer(static_cast<GLenum>(type), 0);

			CHECK_FOR_ERRORS();
		}
		void GraphicsDevice::setBufferData(const BufferType type, const uint32 bytes, void* data, const BufferUsage usage) {
			glBufferData(static_cast<GLenum>(type), bytes, data, static_cast<GLenum>(usage));

			CHECK_FOR_ERRORS();
		}
		void GraphicsDevice::setBufferSubData(const BufferType type, const uint32 offset, const uint32 bytes, void* data) {
			glBufferSubData(static_cast<GLenum>(type), offset, bytes, data);

			CHECK_FOR_ERRORS();
		}

		void GraphicsDevice::drawArrays(const RenderMode mode, const uint32 first, const uint32 last) {
			glDrawArrays(static_cast<GLenum>(mode), first, last);

			CHECK_FOR_ERRORS();
		}
		void GraphicsDevice::drawElements(const RenderMode mode, const PrimitiveType type, const uint32 count, const uint32 indices) {
			glDrawElements(static_cast<GLenum>(mode), count, static_cast<GLenum>(type), (void*)indices);

			CHECK_FOR_ERRORS();
		}

		void GraphicsDevice::createVertexAttributePointer(const VertexAttributePointerDescription& description) {
			glEnableVertexAttribArray(description.location);

			glVertexAttribPointer(description.location,
								  description.count,
								  static_cast<GLenum>(description.type),
								  description.normalized,
								  description.stride,
								  (void*)description.offset);

			CHECK_FOR_ERRORS();
		}
		void GraphicsDevice::disableVertexAttributePointer(const uint32 location) {
			glDisableVertexAttribArray(location);
			
			CHECK_FOR_ERRORS();
		}

		GraphicsDevice::~GraphicsDevice() {
			delete impl;
		}
	}
}

