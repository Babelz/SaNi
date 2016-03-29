#include "sani/platform/graphics/screen_shader_source.hpp"
#include "sani/platform/graphics/descriptions.hpp"
#include "sani/platform/graphics/render_target_2d.hpp"
#include "sani/platform/graphics/graphics_device.hpp"
#include "sani/platform/graphics/viewport.hpp"
#include "sani/debug.hpp"

#include <sstream>
#include <vector>

// Contains WindowsGL and LinuxGL implementations of the graphics device.

#if SANI_TARGET_PLATFORM == SANI_PLATFORM_WINDOWS

#include "GL/wglew.h"
#include "GL/glew.h"

/*
	Remainder...
		Func call ->
			1) GL/Device calls
			2) State WRITE
				ret
*/

#define PUSH_ERROR(message)			pushError(message, __FUNCTION__, __LINE__)
#define CHECK_FOR_API_ERRORS		checkForAPIErrors(__FUNCTION__, __LINE__)

#if _DEBUG
#define CHECKED_API_CALL(fnc)		fnc; CHECK_FOR_API_ERRORS; if (hasErrors()) return
#else
#define CHECKED_API_CALL(fnc)		fnc
#endif

// Common impl of the graphics device.
namespace sani {

	namespace graphics {

		const uint32 ArrayBufferIndex = 0;
		const uint32 ElementArrayBufferIndex = 1;

		struct VertexAttributePointerState {
			bool valid { false };

			VertexAttributePointerDescription desc;

			VertexAttributePointerState() = default;
			
			~VertexAttributePointerState() = default;
		};

		struct DeviceState final {
			Viewport viewport;

			std::vector<std::pair<bool, VertexAttributePointerDescription>> vertexPointers;
			
			uint32 windowedLocationX	{ 0 };
			uint32 windowedLocationY	{ 0 };

			uint32 buffers[2];
			uint32 effect				{ 0 };
			uint32 texture				{ 0 };

			RenderTarget2D* renderTarget	{ nullptr };

			DeviceState() {
				vertexPointers.resize(4);

				buffers[0] = NULL;
				buffers[1] = NULL;
			}

			void invalidateBuffer(const uint32 id) {
				if (buffers[ArrayBufferIndex] == id)		buffers[ArrayBufferIndex]			= NULL;
				if (buffers[ElementArrayBufferIndex] == id) buffers[ElementArrayBufferIndex]	= NULL;
			}
			void invalidateEffect(const uint32 id) {
				if (effect == id) effect = NULL;
			}
			void invalidateRenderTarget(const uint32 fbid) {
				if (renderTarget == nullptr) return;

				if (renderTarget->getFramebuffer() == fbid) renderTarget = nullptr;
			}
			void invalidateTexture(const uint32 id) {
				if (texture == id) texture = NULL;
			}

			~DeviceState() = default;
		};

		struct Impl final {
			uint32 backbufferWidth				{ 0 };
			uint32 backbufferHeight				{ 0 };
			uint32 samples						{ 0 };

			RenderTarget2D* backbuffer			{ nullptr };
			RenderTarget2D* msaBackbuffer		{ nullptr };
			uint32 backbufferEffect;

			std::vector<DeviceState> states;
			DeviceState* currentState			{ nullptr };

			HGLRC renderingContext;
			HDC deviceContext;

			HWND hwnd;
			HINSTANCE hInstance;

			uint32 screenBuffer					{ 0 };

			bool fullscreen						{ false };

			Impl() = default;

			~Impl() {
				delete msaBackbuffer;
			}
		};

		GraphicsDevice::GraphicsDevice(const HWND hWnd, const HINSTANCE hInstance) : impl(new Impl()) {
			impl->hwnd = hWnd;
			impl->hInstance = hInstance;
			impl->deviceContext = GetDC(hWnd);

			impl->states.push_back(DeviceState());
			impl->currentState = &impl->states.back();

			SANI_INIT_EVENT(backbufferSizeChanged, void(const uint32, const uint32, const uint32, const uint32));
			SANI_INIT_EVENT(viewportSizeChanged, void(const Viewport&, const Viewport&));
		}

		void GraphicsDevice::pushError(const String& message, const char* const fnc, const uint32 ln) {
			errorBuffer.push(GraphicsError(message, fnc, ln));
		}
		void GraphicsDevice::checkForAPIErrors(const char* const fnc, const uint32 ln) {
			auto errorCode = glGetError();

			while (errorCode != 0) {
				errorBuffer.push(GraphicsError(errorCode, fnc, ln));

				errorCode = glGetError();
			}
		}

		uint32 GraphicsDevice::compileShader(const char* const src, const ShaderType type, String& error) {
			const auto shader = type == ShaderType::Vertex ? glCreateShader(GL_VERTEX_SHADER) : glCreateShader(GL_FRAGMENT_SHADER);

			auto status = 0;

			glShaderSource(shader, 1, &src, nullptr);
			glCompileShader(shader);
			glGetShaderiv(shader, GL_COMPILE_STATUS, &status);

			if (status == GL_FALSE)  {
				auto loglen = 0;

				auto buff = new char[loglen];

				glGetShaderiv(shader, GL_INFO_LOG_LENGTH, &loglen);
				glGetShaderInfoLog(shader, loglen, &loglen, buff);

				error = String(buff);
				delete buff;

				return NULL;
			}

			return shader;
		}

		bool GraphicsDevice::createContext() {
			// Create context.
			const auto context = wglCreateContext(impl->deviceContext);

			if (context == NULL) {
				PUSH_ERROR("could not create context");

				return false;
			}

			wglMakeCurrent(impl->deviceContext, context);

			impl->renderingContext = context;

			return true;
		}
		bool GraphicsDevice::initializeGlew() {
			const auto glewState = glewInit();

			if (glewState != GLEW_OK) {
				PUSH_ERROR("could not initialize glew!");

				return false;
			}

			return true;
		}
		bool GraphicsDevice::initializeDevice() {
			RECT clntRect;
			GetClientRect(impl->hwnd, &clntRect);

			const Viewport viewport(0, 0, clntRect.right - clntRect.left, clntRect.bottom - clntRect.top);

			CHECKED_API_CALL(glEnable(GL_BLEND))								false;
			CHECKED_API_CALL(glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA)) false;

			glViewport(0, 0, viewport.width, viewport.height);

			impl->msaBackbuffer = impl->samples == NULL ? nullptr : new RenderTarget2D(this, impl->backbufferWidth, impl->backbufferHeight, impl->samples);
			impl->backbuffer = new RenderTarget2D(this, impl->backbufferWidth, impl->backbufferHeight);

			impl->currentState->viewport = viewport;

			return !hasErrors();
		}

		void GraphicsDevice::setupScreenShader() {
			const GLfloat quadVertices[] = {
				// Positions   // TexCoords
				-1.0f, 1.0f, 0.0f, 1.0f,
				-1.0f, -1.0f, 0.0f, 0.0f,
				1.0f, -1.0f, 1.0f, 0.0f,

				-1.0f, 1.0f, 0.0f, 1.0f,
				1.0f, -1.0f, 1.0f, 0.0f,
				1.0f, 1.0f, 1.0f, 1.0f
			};

			BufferDescription desc;
			desc.type = BufferType::ArrayBuffer;
			desc.usage = BufferUsage::Static;
			desc.bytes = sizeof(quadVertices) * sizeof(float);
			desc.data = (void*)quadVertices;

			const auto buffer = createBuffer(&desc);
			if (hasErrors()) return;

			const auto effect = compileEffect(ScreenShaderVertexSource, ScreenShaderFragmentSource);
			if (hasErrors()) return;

			impl->screenBuffer = buffer;
			impl->backbufferEffect = effect;
		}

		void GraphicsDevice::initialize(const int32 backBufferWidth, const int32 backBufferHeight, const uint32 samples) {
			SANI_ASSERT(backBufferWidth != 0);
			SANI_ASSERT(backBufferHeight != 0);

			impl->samples = samples;
			impl->backbufferWidth = backBufferWidth;
			impl->backbufferHeight = backBufferHeight;

			if (!createContext()) return;

			if (!initializeGlew()) return;

			if (!initializeDevice()) return;

			setupScreenShader();
		}
		void GraphicsDevice::dispose() {
			wglDeleteContext(impl->renderingContext);
			wglMakeCurrent(impl->deviceContext, NULL);
		}

		GraphicsError GraphicsDevice::nextError() {
			const auto next = errorBuffer.top();
			errorBuffer.pop();

			return next;
		}
		bool GraphicsDevice::hasErrors() {
			return !errorBuffer.empty();
		}

		bool GraphicsDevice::isFullscreen() const {
			return impl->fullscreen;
		}
		void GraphicsDevice::fullscreen() {
			RECT wndRect;

			GetWindowRect(impl->hwnd, &wndRect);

			// Set style to fullscreen.
			SetWindowLongPtr(impl->hwnd, GWL_STYLE, WS_SYSMENU | WS_POPUP | WS_CLIPCHILDREN | WS_VISIBLE);

			// Get current monitors size.
			const uint32 width = GetSystemMetrics(SM_CXSCREEN);
			const uint32 height = GetSystemMetrics(SM_CYSCREEN);

			MoveWindow(impl->hwnd, 0, 0, width, height, TRUE);
		
			// Store the location of the window.
			impl->currentState->windowedLocationX = wndRect.left;
			impl->currentState->windowedLocationY = wndRect.top;
		}
		void GraphicsDevice::windowed() {
			RECT wndRect;
			RECT rect;

			GetWindowRect(impl->hwnd, &wndRect);

			const uint32 width = wndRect.right - wndRect.left;
			const uint32 height = wndRect.bottom - wndRect.top;

			rect.left = impl->currentState->windowedLocationX;
			rect.top = impl->currentState->windowedLocationY;
			rect.bottom = height;
			rect.right = width;

			SetWindowLongPtr(impl->hwnd, GWL_STYLE, WS_OVERLAPPEDWINDOW | WS_VISIBLE);
			AdjustWindowRect(&rect, WS_OVERLAPPEDWINDOW, FALSE);
			MoveWindow(impl->hwnd, impl->currentState->windowedLocationX, impl->currentState->windowedLocationY, width, height, TRUE);
		}

		void GraphicsDevice::setBackbufferSize(const uint32 width, const uint32 height) {
			impl->backbufferWidth = width;
			impl->backbufferHeight = height;
		}
		uint32 GraphicsDevice::getBackbufferWidth() const {
			return impl->backbufferWidth;
		}
		uint32 GraphicsDevice::getBackbufferHeight() const {
			return impl->backbufferHeight;
		}

		void GraphicsDevice::setSamplesCount(const uint32 samples) {
			impl->samples = samples;
		}
		uint32 GraphicsDevice::getSamplesCount() const {
			return impl->samples;
		}

		void GraphicsDevice::applyBackbufferChanges() {
			const auto oldWidth = getBackbufferWidth();
			const auto oldHeight = getBackbufferHeight();

			auto* oldMsaBackbuffer = impl->msaBackbuffer;
			auto* oldBackbuffer = impl->backbuffer;

			// Delete last msa buffer.
			if (oldMsaBackbuffer != nullptr) {
				oldMsaBackbuffer->dispose();
				
				delete oldMsaBackbuffer;
				
				oldMsaBackbuffer = nullptr;
			}

			oldBackbuffer->dispose();

			delete oldBackbuffer;
			
			const auto newWidth = impl->backbufferWidth;
			const auto newHeight = impl->backbufferHeight;

			impl->msaBackbuffer = impl->samples == NULL ? nullptr : new RenderTarget2D(this, newWidth, newHeight, impl->samples);
			impl->backbuffer = new RenderTarget2D(this, newWidth, newHeight);

			SANI_TRIGGER_EVENT(backbufferSizeChanged,
							   void(const uint32, const uint32, const uint32, const uint32),
							   oldWidth, oldHeight, newHeight, newWidth);

			if (impl->currentState->renderTarget == nullptr) setRenderTarget(impl->msaBackbuffer);
		}

		void GraphicsDevice::setRenderTarget(RenderTarget2D* const renderTarget) {
			RenderTarget2D* const defaultBackbuffer = impl->msaBackbuffer == nullptr ? impl->backbuffer : impl->msaBackbuffer;

			impl->currentState->renderTarget = renderTarget == nullptr ? defaultBackbuffer : renderTarget;

			CHECKED_API_CALL(glBindFramebuffer(GL_FRAMEBUFFER, impl->currentState->renderTarget->getFramebuffer()));

			const auto r = impl->currentState->renderTarget->getClearRed();
			const auto g = impl->currentState->renderTarget->getClearGreen();
			const auto b = impl->currentState->renderTarget->getClearBlue();
			const auto a = impl->currentState->renderTarget->getClearAlpha();

			glClearColor(r, g, b, a);

			CHECKED_API_CALL(glClear(GL_COLOR_BUFFER_BIT));
		}

		void GraphicsDevice::setViewport(const Viewport& viewport) {
			glViewport(viewport.x, viewport.y, viewport.width, viewport.height);

			impl->currentState->viewport = viewport;
		}
		const Viewport& GraphicsDevice::getViewport() const {
			return impl->currentState->viewport;
		}

		// Buffer related.
		uint32 GraphicsDevice::createBuffer(const BufferDescription* const desc) {
			SANI_ASSERT(desc != nullptr);

			uint32 id = 0;

			glGenBuffers(1, &id);
			bindBuffer(desc->type, id);

			CHECKED_API_CALL(glBufferData(static_cast<GLenum>(desc->type), desc->bytes, desc->data, static_cast<GLenum>(desc->usage))) NULL;
			bindBuffer(desc->type, NULL);

			return id;
		}
		void GraphicsDevice::deleteBuffer(const uint32 id) {
			SANI_ASSERT(id != NULL);

			glDeleteBuffers(1, &id);

			for (auto& state : impl->states) state.invalidateBuffer(id);
		}
		void GraphicsDevice::bindBuffer(const BufferType target, const uint32 id) {
			CHECKED_API_CALL(glBindBuffer(static_cast<GLenum>(target), id));

			impl->currentState->buffers[static_cast<uint32>(target)] = id;
		}
		void GraphicsDevice::setBufferData(const BufferType target, const void* const data, const uint32 bytes, const uint32 offset) {
			const uint32 buffer = impl->currentState->buffers[static_cast<uint32>(target)];

			if (buffer == NULL) {
				PUSH_ERROR("buffer type not binded");

				return;
			}

			CHECKED_API_CALL(glBufferSubData(static_cast<GLenum>(target), offset, bytes, data));
		}

		// Texture related.
		void GraphicsDevice::bindTexture(const TextureTarget target, const uint32 id) {
			CHECKED_API_CALL(glBindTexture(static_cast<GLenum>(target), id));

			impl->currentState->texture = id;
		}
		uint32 GraphicsDevice::createTexture(const TextureDescription* desc) {
			SANI_ASSERT(desc != nullptr);

			uint32 id = 0;

			glGenTextures(1, &id);
			glBindTexture(GL_TEXTURE_2D, id);

			setTextureData(TextureTarget::Texture2D, 0, desc->format, desc->width, desc->height, desc->format, nullptr);

			glBindTexture(GL_TEXTURE_2D, NULL);

			return id;
		}

		static bool asd = false;

		void GraphicsDevice::createRendertarget(uint32& texid, uint32& fbid, const uint32 width, const uint32 height, const uint32 samples) {
			glGenFramebuffers(1, &fbid);
			glBindFramebuffer(GL_FRAMEBUFFER, fbid);

			// Generate texture.
			glGenTextures(1, &texid);

			GLenum target = samples == NULL ? GL_TEXTURE_2D : GL_TEXTURE_2D_MULTISAMPLE;

			if (target == GL_TEXTURE_2D) {
				glBindTexture(GL_TEXTURE_2D, texid);

				CHECKED_API_CALL(glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, width, height, 0, GL_RGBA, GL_UNSIGNED_BYTE, NULL));
				CHECKED_API_CALL(glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR));
				CHECKED_API_CALL(glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR));
			} else {
				glBindTexture(GL_TEXTURE_2D_MULTISAMPLE, texid);

				CHECKED_API_CALL(glTexImage2DMultisample(GL_TEXTURE_2D_MULTISAMPLE, samples, GL_RGBA, width, height, GL_TRUE));
			}

			CHECKED_API_CALL(glFramebufferTexture2D(GL_FRAMEBUFFER, GL_COLOR_ATTACHMENT0, target, texid, NULL));
			
			if (glCheckFramebufferStatus(GL_FRAMEBUFFER) != GL_FRAMEBUFFER_COMPLETE) errorBuffer.push(GraphicsError("Could not create render target 2D", __FUNCTION__, __LINE__));

			glBindFramebuffer(GL_FRAMEBUFFER, NULL);
			glBindTexture(target, NULL);
		}
		void GraphicsDevice::deleteRenderTarget(const uint32 fbid) {
			CHECKED_API_CALL(glDeleteFramebuffers(1, &fbid));

			for (auto& state : impl->states) state.invalidateRenderTarget(fbid);
		}

		void GraphicsDevice::setTextureParameter(const TextureTarget target, const TextureParameterName field, const int32 value) {
			CHECKED_API_CALL(glTexParameteri(static_cast<GLenum>(target), static_cast<GLenum>(field), static_cast<GLuint>(value)));
		}
		void GraphicsDevice::getTextureData(const TextureTarget target, const int32 level, const SurfaceFormat format, unsigned char* data) {
			CHECKED_API_CALL(glGetTexImage(static_cast<GLenum>(target),
										   level,
										   static_cast<GLint>(format),
										   GL_UNSIGNED_BYTE,
										   data));
		}
		void GraphicsDevice::setTextureData(const TextureTarget target, const int32 level, const SurfaceFormat internalFormat, const int32 width, const int32 height, const SurfaceFormat format, const unsigned char* data) {
			CHECKED_API_CALL(glTexImage2D(static_cast<GLenum>(target),
										  level,
										  static_cast<GLint>(internalFormat),
										  width,
										  height,
										  0,
										  static_cast<GLint>(format),
										  GL_UNSIGNED_BYTE,
										  data));
		}

		void GraphicsDevice::deleteTexture(const uint32 texid) {
			glDeleteTextures(1, &texid);

			for (auto& state : impl->states) state.invalidateTexture(texid);
		}
		
		// Effect related.
		void GraphicsDevice::bindEffect(const uint32 id) {
			CHECKED_API_CALL(glUseProgram(id));

			impl->currentState->effect = id;
		}

		int32 GraphicsDevice::getUniformsCount() {
			int32 count = 0;

			CHECKED_API_CALL(glGetProgramiv(impl->currentState->effect, GL_ACTIVE_UNIFORMS, &count)) NULL;

			return count;
		}
		int32 GraphicsDevice::getUniformLocation(const String& name) {
			return CHECKED_API_CALL(glGetUniformLocation(impl->currentState->effect, name.c_str())) NULL;
		}

		void GraphicsDevice::getUniformInformation(const uint32 index, uint32& location, String& name, uint32& type, int32& valuesCount) {
			char namebuff[128];

			int32 namelen = -1;

			// Get name len, values, count, type and name.
			CHECKED_API_CALL(glGetActiveUniform(impl->currentState->effect, index, sizeof(namebuff)-1, &namelen, &valuesCount, &type, namebuff));

			// Copy name if we got the info.
			if (namelen != -1) name = String(std::begin(namebuff), std::begin(namebuff) + namelen);

			// Get location of the uniform.
			location = getUniformLocation(name);
		}
		void GraphicsDevice::setUniformValue(const String& name, const void* const data, const UniformType type) {
			const auto location = getUniformLocation(name);

			if (location == -1) {
				PUSH_ERROR("invalid uniform name");

				return;
			}

			if		(type == UniformType::Float32)		{ CHECKED_API_CALL(glUniform1f(location, *static_cast<const GLfloat* const>(data))); }
			else if (type == UniformType::Mat3F)		{ CHECKED_API_CALL(glUniformMatrix3fv(location, 1, GL_FALSE, static_cast<const GLfloat* const>(data))); }
			else if (type == UniformType::Mat4F)		{ CHECKED_API_CALL(glUniformMatrix4fv(location, 1, GL_FALSE, static_cast<const GLfloat* const>(data))); }
			else										{ PUSH_ERROR("invalid uniform type"); }
		}

		uint32 GraphicsDevice::compileEffect(const char* const vscr, const char* const fscr, String& errors) {
			String vserror;
			const auto vs = compileShader(vscr, ShaderType::Vertex, vserror);

			String fserror;
			const auto fs = compileShader(fscr, ShaderType::Fragment, fserror);
			
			if (vs == NULL || fs == NULL) {
				std::stringstream ss;
				
				if (!vserror.empty()) {
					ss << "vs err: ";
					ss << vserror;
				}
				
				if (fserror.empty()) {
					ss << " - ";
					ss << "fs err: ";
					ss << fserror;
				}

				errors = ss.str();

				return NULL;
			}

			// Shaders compile ok, return.
			const auto pid = glCreateProgram();
			glAttachShader(pid, vs);
			glAttachShader(pid, fs);
			glLinkProgram(pid);

			auto status = 0;
			glGetProgramiv(pid, GL_LINK_STATUS, &status);

			if (status == GL_FALSE) {
				PUSH_ERROR("could not link program");

				return NULL;
			}

			return pid;
		}
		uint32 GraphicsDevice::compileEffect(const char* const vscr, const char* const fscr) {
			String errors; // Not used.

			return compileEffect(vscr, fscr, errors);
		}
		void GraphicsDevice::deleteEffect(const uint32 id) {
			CHECKED_API_CALL(glDeleteProgram(id));

			for (auto& state : impl->states) state.invalidateEffect(id);
		}

		// Vertex pointer related.
		void GraphicsDevice::createVertexPointer(const VertexAttributePointerDescription* const desc) {
			CHECKED_API_CALL(glEnableVertexAttribArray(desc->location));
			
			CHECKED_API_CALL(glVertexAttribPointer(desc->location,
												   desc->size, 
												   static_cast<GLenum>(desc->type), 
												   desc->normalized, 
												   desc->stride, 
												   (void*)desc->offset));
			
			// Register.
			if (impl->currentState->vertexPointers.size() < desc->location) impl->currentState->vertexPointers.resize(desc->location);
			
			impl->currentState->vertexPointers[desc->location].first = true;
			impl->currentState->vertexPointers[desc->location].second = *desc;
		}
		void GraphicsDevice::disableVertexPointer(const uint32 location) {
			CHECKED_API_CALL(glDisableVertexAttribArray(location));

			if (impl->currentState->vertexPointers.size() < location) return;

			impl->currentState->vertexPointers[location].first = false;
		}

		void GraphicsDevice::clear(const float32 r, const float32 g, const float32 b, const float32 a) {
			setRenderTarget(nullptr);

			glClearColor(r, g, b, a);
			
			SwapBuffers(impl->deviceContext);
			
			glClear(GL_COLOR_BUFFER_BIT);

			CHECK_FOR_API_ERRORS;
		}
		void GraphicsDevice::present(const uint32 effect) {			
			const auto width = impl->backbuffer->getWidth();
			const auto height = impl->backbuffer->getHeight();

			if (impl->msaBackbuffer != nullptr) {
				// Copy from MSA backbuffer to "draw" backbuffer. Using sampling.
				CHECKED_API_CALL(glBindFramebuffer(GL_READ_FRAMEBUFFER, impl->msaBackbuffer->getFramebuffer()));
				CHECKED_API_CALL(glBindFramebuffer(GL_DRAW_FRAMEBUFFER, impl->backbuffer->getFramebuffer()));
				CHECKED_API_CALL(glBlitFramebuffer(0, 0, width, height, 0, 0, width, height, GL_COLOR_BUFFER_BIT, GL_NEAREST));
			}

			// Go back to default back buffer.
			glBindFramebuffer(GL_FRAMEBUFFER, NULL);
			glClearColor(0.0f, 0.0f, 0.0f, 1.0f);
			glClear(GL_COLOR_BUFFER_BIT);

			// Bind back buffer texture.
			glBindTexture(GL_TEXTURE_2D, impl->backbuffer->getID());

			const auto postproceff = effect == NULL ? impl->backbufferEffect : effect;

			CHECKED_API_CALL(glUseProgram(postproceff));
			CHECKED_API_CALL(glBindBuffer(GL_ARRAY_BUFFER, impl->screenBuffer));

			const auto VtxDescLocation = 0;
			const auto TexDescLocation = 1;
			const auto ScreenVertexElementsCount = 4;

			static VertexAttributePointerDescription vtxDesc;
			vtxDesc.location = VtxDescLocation;
			vtxDesc.size = 2;
			vtxDesc.type = PrimitiveType::Float;
			vtxDesc.normalized = false;
			vtxDesc.stride = sizeof(float32) * ScreenVertexElementsCount;
			vtxDesc.offset = 0;

			static VertexAttributePointerDescription texDesc;
			texDesc.location = TexDescLocation;
			texDesc.size = 2;
			texDesc.type = PrimitiveType::Float;
			texDesc.normalized = false;
			texDesc.stride = sizeof(float32) * ScreenVertexElementsCount;
			texDesc.offset = sizeof(float32) * 2;

			createVertexPointer(&vtxDesc);
			createVertexPointer(&texDesc);

			drawArrays(RenderMode::Triangles, 0, 6);

			disableVertexPointer(VtxDescLocation);
			disableVertexPointer(TexDescLocation);
		}
		void GraphicsDevice::drawArrays(const RenderMode mode, const uint32 first, const uint32 last) {
			CHECKED_API_CALL(glDrawArrays(static_cast<GLenum>(mode), first, last - first));
		}
		void GraphicsDevice::drawElements(const RenderMode mode, const PrimitiveType type, const uint32 count, const uint32 indices) {
			CHECKED_API_CALL(glDrawElements(static_cast<GLenum>(mode), count, static_cast<GLenum>(type), (void*)indices));
		}

		void GraphicsDevice::resumeState() {
			// TODO: impl.
		}
		void GraphicsDevice::saveState() {
			// TODO: impl.
		}

		GraphicsDevice::~GraphicsDevice() {
			delete impl;
		}
	}
}

#endif