#include "sani/platform/graphics/screen_shader_source.hpp"
#include "sani/platform/graphics/graphics_device_state.hpp"
#include "sani/platform/graphics/render_target_2d.hpp"
#include "sani/platform/graphics/graphics_device.hpp"
#include "sani/platform/graphics/viewport.hpp"
#include "sani/debug.hpp"

#include <sstream>
#include <stdexcept>
#include <stack>

// Contains WindowsGL and LinuxGL implementations of the graphics device.

/*
	Common implementation declaration.
*/
namespace sani {

	namespace graphics {

		using StateStack = std::stack<GraphicsDeviceState>;

		class GraphicsDevice::Cimpl {
		public:
			StateStack states;
			GraphicsDeviceState* currentState;

			VertexAttributePointerDescription vertexDescription;
			VertexAttributePointerDescription textureDescription;

			RenderTarget2D* defaultRenderTarget;
			RenderTarget2D* currentRenderTarget;

			Viewport viewport;

			uint32 backBufferWidth;
			uint32 backBufferHeight;

			uint32 screenBuffer;

			Cimpl() : backBufferWidth(0),
					  backBufferHeight(0),
					  currentRenderTarget(nullptr),
					  defaultRenderTarget(nullptr),
					  screenBuffer(0) {

				vertexDescription.location = 0;
				vertexDescription.count = 2;
				vertexDescription.type = PrimitiveType::Float;
				vertexDescription.normalized = false;
				vertexDescription.stride = sizeof(float32)* 4;
				vertexDescription.offset = 0;

				textureDescription.location = 1;
				textureDescription.count = 2;
				textureDescription.type = PrimitiveType::Float;
				textureDescription.normalized = false;
				textureDescription.stride = sizeof(float32)* 4;
				textureDescription.offset = sizeof(float32)* 2;

				states.push(GraphicsDeviceState());
				currentState = &states.top();
			}

			~Cimpl() {
			}
		};
	}
}

#if SANI_TARGET_PLATFORM == SANI_PLATFORM_WINDOWS

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

			uint32 screenShader;

			// Common impl.
			Cimpl cImpl;

			Impl() : renderingContext(NULL),
				     deviceContext(NULL),
			      	 hWnd(NULL),
					 hInstance(NULL),
					 fullscreen(false),
					 windowedLocationX(0),
					 windowedLocationY(0),
					 screenShader(0) {
			}
		};

		GraphicsDevice::GraphicsDevice(const HWND hWnd, const HINSTANCE hInstance, const int32 backBufferWidth, const int32 backBufferHeight) : impl(new Impl())  {
			impl->hWnd = hWnd;
			impl->hInstance = hInstance;
			impl->deviceContext = GetDC(hWnd);
			impl->cImpl.backBufferWidth = backBufferWidth;
			impl->cImpl.backBufferHeight = backBufferHeight;

			SANI_INIT_EVENT(backbufferSizeChanged, void(const uint32, const uint32, const uint32, const uint32));
			SANI_INIT_EVENT(viewportSizeChanged, void(const Viewport&, const Viewport&));
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
			impl->renderingContext = wglCreateContext(impl->deviceContext);
			wglMakeCurrent(impl->deviceContext, impl->renderingContext);

			GLenum state = glewInit();

			if (state != GLEW_OK) {
				// 1282 invalid operation.
				// TODO: translate to some human readable error messages.
				errorBuffer.push(GRAPHICS_ERROR(1282));
			}

			// Check for pre-init errors.
			IF_ERRORS_RETURN false;

			// Enable GL settings.
			glEnable(GL_BLEND);

			IF_ERRORS_RETURN false;

			glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
			
			// Set the window full screen. Default is windowed.
			if (impl->fullscreen) setFullscreen();

			// Set viewport.
			RECT clntRect;
			GetClientRect(impl->hWnd, &clntRect);

			Viewport viewport(0, 0, clntRect.right - clntRect.left, clntRect.bottom - clntRect.top);

			impl->cImpl.defaultRenderTarget = new RenderTarget2D(this, viewport.width, viewport.height);
			setRenderTarget(nullptr);

			// Post-init error checks.
			IF_ERRORS_RETURN false;

			if (hasErrors()) {
				// Clean up before returning.
				cleanUp();

				return false;
			}

			setViewport(viewport);

			// Create the screen shader.
			createScreenShader();

			// Create the screen buffer.
			const GLfloat quadVertices[] = {
				// Positions   // TexCoords
				-1.0f, 1.0f, 0.0f, 1.0f,
				-1.0f, -1.0f, 0.0f, 0.0f,
				1.0f, -1.0f, 1.0f, 0.0f,

				-1.0f, 1.0f, 0.0f, 1.0f,
				1.0f, -1.0f, 1.0f, 0.0f,
				1.0f, 1.0f, 1.0f, 1.0f
			};

			glGenBuffers(1, &impl->cImpl.screenBuffer);
			glBindBuffer(GL_ARRAY_BUFFER, impl->cImpl.screenBuffer);
			glBufferData(GL_ARRAY_BUFFER, sizeof(quadVertices), quadVertices, GL_STATIC_DRAW);

			// No errors, init ok.
			return true;
		}
		void GraphicsDevice::createScreenShader() {
			uint32 vertex = 0;
			uint32 fragment = 0;
			uint32 effect = 0;

			compileShader(vertex, ScreenShaderVertexSource, ShaderType::Vertex);
			IF_ERRORS_RETURN;

			compileShader(fragment, ScreenShaderFragmentSource, ShaderType::Fragment);
			IF_ERRORS_RETURN;

			createProgram(impl->screenShader);
			linkToProgram(impl->screenShader, vertex, true);
			linkToProgram(impl->screenShader, fragment, true);
			linkProgram(impl->screenShader);
			IF_ERRORS_RETURN;
		}

		bool GraphicsDevice::cleanUp() {
			IF_ERRORS_RETURN false;

			// Swap context and delete it.
			wglDeleteContext(impl->renderingContext);
			wglMakeCurrent(impl->deviceContext, NULL);

			// Check for windows errors.
			DWORD error = GetLastError();

			return hasErrors();
		}

		void GraphicsDevice::clear(const float32 r, const float32 g, const float32 b, const float32 a) {
			setRenderTarget(nullptr);

			glClearColor(r, g, b, a);

			SwapBuffers(impl->deviceContext);

			glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

			CHECK_FOR_ERRORS;
		}
		void GraphicsDevice::present() {
			//Draw the last frame to back buffer.
			glBindFramebuffer(GL_FRAMEBUFFER, 0); 
			glClearColor(0.0f, 0.0f, 0.0f, 1.0f);
			glClear(GL_COLOR_BUFFER_BIT);

			glBindTexture(GL_TEXTURE_2D, impl->cImpl.currentRenderTarget->getID());

			useProgram(impl->screenShader);
			
			glBindBuffer(GL_ARRAY_BUFFER, impl->cImpl.screenBuffer);

			this->createVertexAttributePointer(impl->cImpl.vertexDescription);
			this->createVertexAttributePointer(impl->cImpl.textureDescription);

			glDrawArrays(GL_TRIANGLES, 0, 6);

			glDisableVertexAttribArray(0);
			glDisableVertexAttribArray(1);
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

			CHECK_FOR_ERRORS;
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
			const Viewport oldViewport = impl->cImpl.viewport;

			impl->cImpl.currentState->viewport = viewport;
			impl->cImpl.viewport = viewport;

			glViewport(impl->cImpl.viewport.x, impl->cImpl.viewport.y,
				       impl->cImpl.viewport.width, impl->cImpl.viewport.height);

			SANI_TRIGGER_EVENT(viewportSizeChanged, 
							   void(const Viewport&, const Viewport&),
							   oldViewport, viewport);

			CHECK_FOR_ERRORS;
		}
		Viewport GraphicsDevice::getViewport() const {
			return impl->cImpl.viewport;
		}

		void GraphicsDevice::bindTexture(const uint32 texture) {
			impl->cImpl.currentState->texture = texture;

			glBindTexture(GL_TEXTURE_2D, texture);

			CHECK_FOR_ERRORS;
		}
		void GraphicsDevice::unbindTexture() {
			impl->cImpl.currentState->texture = 0;

			glBindTexture(GL_TEXTURE_2D, 0);
			
			CHECK_FOR_ERRORS;
		}

		void GraphicsDevice::setRenderTarget(RenderTarget2D* renderTarget) {
			impl->cImpl.currentRenderTarget = renderTarget == nullptr ? impl->cImpl.defaultRenderTarget : renderTarget;
			
			// Don't store default render target.
			if (renderTarget != nullptr) impl->cImpl.currentState->renderTarget = impl->cImpl.currentRenderTarget;

			glBindFramebuffer(GL_FRAMEBUFFER, impl->cImpl.currentRenderTarget->getFramebuffer());

			glClearColor(1.0f, 1.0f, 1.0f, 1.0f);
			glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

			CHECK_FOR_ERRORS;
		}

		int32 GraphicsDevice::surfaceFormatToOpenGL(const SurfaceFormat fmt) {
			GLint glFormat = 0;
			
			switch (fmt) {
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

			const GLint glFormat = GraphicsDevice::surfaceFormatToOpenGL(desc.format);

			setTextureData(TextureTarget::Texture2D, 0, desc.format, desc.width, desc.height, desc.format, nullptr);
			
			glBindTexture(GL_TEXTURE_2D, 0);

			CHECK_FOR_ERRORS;
		}

		void GraphicsDevice::setTextureParameter(const TextureTarget target, const TextureParameterName field, int value) {
			glTexParameteri(static_cast<GLenum>(target), static_cast<GLenum>(field), static_cast<GLuint>(value));
		}

		void GraphicsDevice::setTextureData(const TextureTarget target, const int level, const SurfaceFormat internalFormat,
											const int width, const int height, const SurfaceFormat format, const unsigned char* data) {

			const GLint glformat = surfaceFormatToOpenGL(format);
			const GLint internalGlformat = surfaceFormatToOpenGL(format);
			
			glTexImage2D(static_cast<GLenum>(target),
						 level,
						 internalGlformat,
						 width,
						 height,
						 0,
						 glformat,
						 GL_UNSIGNED_BYTE,
						 data);
		}

		void GraphicsDevice::getTextureData(const TextureTarget target, const int level, const SurfaceFormat format, unsigned char* data) {
#if SANI_TARGET_PLATFORM != SANI_PLATFORM_ANDROID
			glGetTexImage(static_cast<GLenum>(target),
						  level,
						  surfaceFormatToOpenGL(format),
						  GL_UNSIGNED_BYTE,
						  data);
#else
			throw std::logic_error("not implemented");
#endif

		}
		void GraphicsDevice::deleteTexture(const uint32 texture) {
			// Check texture.
			if (impl->cImpl.currentState->texture == texture) impl->cImpl.currentState->texture = 0;
				
			// No need to check for the render target, it's state should be 
			// updated in render target specific functions.

			glDeleteTextures(1, &texture);
		}

		void GraphicsDevice::generateRenderTarget2D(uint32& texture, uint32& frameBuffer, const uint32 width, const uint32 height) {
			// Generate frame buffer.
			glGenFramebuffers(1, &frameBuffer);
			glBindFramebuffer(GL_FRAMEBUFFER, frameBuffer);
			
			IF_ERRORS_RETURN;

			// Generate texture.
			glGenTextures(1, &texture);
			glBindTexture(GL_TEXTURE_2D, texture);

			glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, width, height, 0, GL_RGBA, GL_UNSIGNED_BYTE, NULL);
			glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
			glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
			IF_ERRORS_RETURN;

			glFramebufferTexture2D(GL_FRAMEBUFFER, GL_COLOR_ATTACHMENT0, GL_TEXTURE_2D, texture, 0);
			IF_ERRORS_RETURN;

			if (glCheckFramebufferStatus(GL_FRAMEBUFFER) != GL_FRAMEBUFFER_COMPLETE) errorBuffer.push(GraphicsError("Could not create render target 2D", __FUNCTION__, __LINE__));

			glBindFramebuffer(GL_FRAMEBUFFER, 0);
			glBindTexture(GL_TEXTURE_2D, 0);
		}

		void GraphicsDevice::deleteFramebuffer(const uint32 buffer) {
			if (impl->cImpl.currentState->renderTarget != nullptr)
				if (impl->cImpl.currentState->renderTarget->getFramebuffer() == buffer) impl->cImpl.currentState->renderTarget = nullptr;

			glDeleteFramebuffers(1, &buffer);
		}

		void GraphicsDevice::resizeBackbuffer(const uint32 width, const uint32 height) {
			const uint32 oldWidth = impl->cImpl.defaultRenderTarget->getWidth();
			const uint32 oldHeight = impl->cImpl.defaultRenderTarget->getHeight();

			delete impl->cImpl.defaultRenderTarget;

			impl->cImpl.defaultRenderTarget = new RenderTarget2D(this, width, height);

			SANI_TRIGGER_EVENT(backbufferSizeChanged, 
							   void(const uint32, const uint32, const uint32, const uint32),
							   oldWidth, oldHeight, width, height);
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

			CHECK_FOR_ERRORS;

			// Push custom error.
			if (result != GL_TRUE) errorBuffer.push(GraphicsError("Failed to compile shader", __FUNCTION__, __LINE__));
		}
		void GraphicsDevice::deleteShader(const uint32 shader) {
			glDeleteShader(shader);

			CHECK_FOR_ERRORS;
		}

		void GraphicsDevice::createProgram(uint32& program) {
			program = glCreateProgram();

			CHECK_FOR_ERRORS;

			if (program == 0) {
				errorBuffer.push(GraphicsError("Could not create shader program", __FUNCTION__, __LINE__));

				return;
			}
		}
		void GraphicsDevice::linkToProgram(const uint32 program, const uint32 shader, const bool dispose) {
			glAttachShader(program, shader);

			if (dispose) deleteShader(shader);

			CHECK_FOR_ERRORS;
		}
		void GraphicsDevice::linkProgram(const uint32 program) {
			glLinkProgram(program);

			GLint result = 0;

			glGetProgramiv(program, GL_LINK_STATUS, &result);
			
			CHECK_FOR_ERRORS;

			if (result != GL_TRUE) errorBuffer.push(GraphicsError("Failed to link shader to a program", __FUNCTION__, __LINE__));
		}

		void GraphicsDevice::useProgram(const uint32 program) {
			impl->cImpl.currentState->shader = program;

			glUseProgram(program);

			CHECK_FOR_ERRORS;
		}

		void GraphicsDevice::setShaderUniform(const uint32 shader, const char* name, void* data, const UniformType type) {
			glUseProgram(shader);

			GLint uniformLocation = glGetUniformLocation(shader, name);

			// Uniform not found.
			if (uniformLocation == -1) {
				CHECK_FOR_ERRORS;

				std::stringstream ss;

				ss << "Invalid uniform name, uniform not found. Name was \"";
				ss << name;
				ss << "\"";

				errorBuffer.push(GraphicsError(ss.get(), __FUNCTION__, __LINE__));

				return;
			}

			// Set the uniform value.
			switch (type) {
			case UniformType::Mat4F:
				glUniformMatrix4fv(uniformLocation, 1, GL_FALSE, static_cast<GLfloat*>(data));
				break;
			case UniformType::Mat3F:
				glUniformMatrix3fv(uniformLocation, 1, GL_FALSE, static_cast<GLfloat*>(data));
				break;
			case UniformType::Float32:
				glUniform1f(uniformLocation, *static_cast<GLfloat*>(data));
				break;
			default:
				throw std::logic_error("Invalid or unsupported uniform type");
			}

			glUseProgram(0);

			CHECK_FOR_ERRORS;
		}

		int32 GraphicsDevice::getUniformsCount(const uint32 shader) const {
			int32 count = -1;

			glGetProgramiv(shader, GL_ACTIVE_UNIFORMS, &count);

			return count;
		}

		int32 GraphicsDevice::getUniformLocation(const uint32 shader, const String& name) const {
			return glGetUniformLocation(shader, name.c_str());
		}

		void GraphicsDevice::getUniformInformation(const uint32 shader, const int32 index, int32& location, String& name, uint32& type, int32& valuesCount) const {
			char namebuff[128];

			int32 namelen = -1;

			// Get name len, values, count, type and name.
			glGetActiveUniform(shader, index, sizeof(namebuff) - 1, &namelen, &valuesCount, &type, namebuff);
			
			// Copy name if we got the info.
			if (namelen != -1) name = String(std::begin(namebuff), std::begin(namebuff) + namelen);

			// Get location of the uniform.
			location = getUniformLocation(shader, name);
		}

		void GraphicsDevice::generateBuffer(uint32& buffer) {
			glGenBuffers(1, &buffer);

			CHECK_FOR_ERRORS;
		}
		void GraphicsDevice::bindBuffer(uint32& buffer, const BufferType type) {
			impl->cImpl.currentState->bindedBuffers[type] = buffer;

			glBindBuffer(static_cast<GLenum>(type), buffer);

			CHECK_FOR_ERRORS;
		}
		void GraphicsDevice::unbindBuffer(const BufferType type) {
			impl->cImpl.currentState->bindedBuffers.erase(type);

			glBindBuffer(static_cast<GLenum>(type), 0);

			CHECK_FOR_ERRORS;
		}
		void GraphicsDevice::setBufferData(const BufferType type, const uint32 bytes, void* data, const BufferUsage usage) {
			glBufferData(static_cast<GLenum>(type), bytes, data, static_cast<GLenum>(usage));

			CHECK_FOR_ERRORS;
		}
		void GraphicsDevice::setBufferSubData(const BufferType type, const uint32 offset, const uint32 bytes, void* data) {
			glBufferSubData(static_cast<GLenum>(type), offset, bytes, data);

			CHECK_FOR_ERRORS;
		}
		void GraphicsDevice::deleteBuffer(const uint32 buffer) {
			// Check render target.
			auto& buffs = impl->cImpl.currentState->bindedBuffers;
			auto it = buffs.begin();

			while (it != buffs.end()) {
				if (it->second == buffer) {
					buffs.erase(it);

					break;
				}

				it++;
			}

			glDeleteBuffers(1, &buffer);
		}

		void GraphicsDevice::drawArrays(const RenderMode mode, const uint32 first, const uint32 last) {
			glDrawArrays(static_cast<GLenum>(mode), first, last);

			CHECK_FOR_ERRORS;
		}
		void GraphicsDevice::drawElements(const RenderMode mode, const PrimitiveType type, const uint32 count, const uint32 indices) {
			glDrawElements(static_cast<GLenum>(mode), count, static_cast<GLenum>(type), (void*)indices);

			CHECK_FOR_ERRORS;
		}

		void GraphicsDevice::createVertexAttributePointer(const VertexAttributePointerDescription& description) {
			impl->cImpl.currentState->vertexPointers[description.location] = description;

			glEnableVertexAttribArray(description.location);

			glVertexAttribPointer(description.location,
								  description.count,
								  static_cast<GLenum>(description.type),
								  description.normalized,
								  description.stride,
								  (void*)description.offset);

			CHECK_FOR_ERRORS;
		}
		void GraphicsDevice::disableVertexAttributePointer(const uint32 location) {
			impl->cImpl.currentState->vertexPointers.erase(location);

			glDisableVertexAttribArray(location);
			
			CHECK_FOR_ERRORS;
		}

		void GraphicsDevice::bindAttributeLocation(const uint32 shader, const uint32 index, const String& name) {
			glBindAttribLocation(shader, index, name.c_str());
		}

		void GraphicsDevice::saveState() {
			impl->cImpl.states.push(GraphicsDeviceState());
			
			// Copy viewport information.
			GraphicsDeviceState* newState = &impl->cImpl.states.top();
			newState->viewport = impl->cImpl.viewport;

			// Unbind all state stuff.
			setRenderTarget(nullptr);

			// Use raw gl to avoid some state checks.
			for (auto buffer : impl->cImpl.currentState->bindedBuffers) glBindBuffer(static_cast<GLenum>(buffer.first), 0);
			for (auto vp : impl->cImpl.currentState->vertexPointers)	glDisableVertexAttribArray(vp.first);
			glBindTexture(GL_TEXTURE_2D, 0);
			glUseProgram(0);

			// Swap state.
			impl->cImpl.currentState = newState;
		}

		void GraphicsDevice::resumeState() {
			// At primary state.
			if (impl->cImpl.states.size() == 1) return;
			
			// Swap state.
			
			// Pop current.
			impl->cImpl.states.pop();

			// Get last and apply it's state to device.
			GraphicsDeviceState* resumingState = &impl->cImpl.states.top();
			
			setRenderTarget(resumingState->renderTarget);

			// Use raw gl to avoid some state checks.
			for (auto buffer : resumingState->bindedBuffers) glBindBuffer(static_cast<GLenum>(buffer.first), buffer.second);
			
			for (auto vp : resumingState->vertexPointers) {
				glEnableVertexAttribArray(vp.first);

				glVertexAttribPointer(vp.second.location,
									  vp.second.count,
									  static_cast<GLenum>(vp.second.type),
									  vp.second.normalized,
									  vp.second.stride,
									  (void*)vp.second.offset);
			}
			
			glBindTexture(GL_TEXTURE_2D, resumingState->texture);
			glUseProgram(resumingState->shader);

			// Swap.
			impl->cImpl.currentState = resumingState;
		}

		uint32 GraphicsDevice::currentState() const {
			return static_cast<uint32>(impl->cImpl.states.size());
		}

		GraphicsDevice::~GraphicsDevice() {
			delete impl;
		}
	}
}

