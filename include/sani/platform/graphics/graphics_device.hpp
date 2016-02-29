#pragma once

#include "sani/platform/graphics/graphics_error.hpp"
#include "sani/platform/graphics/graphics_precompiled.hpp"
#include "sani/platform/platform_config.hpp"
#include "sani/core/events.hpp"

#include <stack>

#if SANI_TARGET_PLATFORM == SANI_PLATFORM_WIN32

#include <Windows.h>

#endif

#define IF_ERRORS_RETURN checkForErrors(__FUNCTION__, __LINE__); if (hasErrors()) return
#define CHECK_FOR_ERRORS checkForErrors(__FUNCTION__, __LINE__)

namespace sani {
	
	namespace graphics {

		/*
			Viewport size is not tied to anything.
			Default back buffer size is tied to the size of the window.
			If window goes to fullscreen, nothing gets changed.

			Viewport					- tied to nothing, can be changed
			Default back buffer size	- tied to window size, can be changed

			Clientbounds of the window	- not tied to anything, user can change this
				- If changed, resolution of the device stays the same
				  and viewports size stays the same

			Virtual resolution
				- size of the back buffer
			Resolution
				- size of the windows client area 
		*/
		
		// Forward declarations.
		struct Viewport;
		struct TextureDescription;
		class RenderTarget2D;

		using ErrorBuffer = std::stack<GraphicsError>;
		
		/// @class GraphicsDevice graphics_device.hpp "sani/platform/graphics_device.hpp"
		/// @author voidbab
		/// 
		/// A virtual representation of the physical graphics adapter of this machine.
		/// DX contains WinDX and GL contains Linux and WinGL implementations.
		class GraphicsDevice {
		private:
			class Cimpl;
			class Impl;

			Impl* impl;

			ErrorBuffer errorBuffer;

			void checkForErrors(const char* func, const int32 line);

			static int32 surfaceFormatToOpenGL(const SurfaceFormat fmt);
			void createScreenShader();
		public:
#if SANI_TARGET_PLATFORM == SANI_PLATFORM_ANDROID
			GraphicsDevice();
			// Public Win32 members.
#elif SANI_TARGET_PLATFORM == SANI_PLATFORM_WIN32
			
			SANI_DECLARE_EVENT(backbufferSizeChanged, void(const uint32, const uint32, const uint32, const uint32));
			SANI_DECLARE_EVENT(viewportSizeChanged,	void(const Viewport&, const Viewport&));

			GraphicsDevice(const HWND hWnd, const HINSTANCE hInstance, const int32 backBufferWidth, const int32 backBufferHeight);

			bool isFullscreen() const;
			void setFullscreen();
			void setWindowed();
#endif

			/// Returns true if the error buffer contains errors.
			bool hasErrors() const;
			/// Returns the next error from the error buffer.
			GraphicsError getError();

			/// Sets the viewport of the device.
			/// @param[in] viewport viewport to use
			void setViewport(const Viewport& viewport);
			/// Returns the current viewport to the user.
			Viewport getViewport() const;

			/// Initializes the device.
			bool initialize();
			/// Cleans the device.
			bool cleanUp();

			/// Clears the device. Swaps the back
			/// and front buffer.
			void clear(const float32 r, const float32 g, const float32 b, const float32 a);
			void present();
			
			/*
				Texture and render target operations.
			*/

			/// Binds given texture.
			/// @param[in] texture texture to bind
			void bindTexture(const uint32 texture);
			/// Unbinds current texture.
			void unbindTexture();
			
			/// Sets the current render target for the device.
			/// If the value is null, default render target
			/// will be used.
			void setRenderTarget(RenderTarget2D* renderTarget);

			/// Creates an empty texture or rendertarget
			void generateTexture(uint32& texture, const TextureDescription& desc);
			/// Generates new render target.
			/// @param[in] renderTexture texture to be used with the target, call generateTexture before passing it
			/// @param[in] colorBuffer color buffer to be generated for the target
			/// @param[in] frameBuffer frame buffer to be generated for the target
			/// @param[in] depthBuffer depth buffer to be generated for the target
			/// @param[in] width width of the render target
			/// @param[in] height of the render target
			void generateRenderTarget2D(uint32& texture, uint32& frameBuffer, const uint32 width, const uint32 height);

			void resizeBackbuffer(const uint32 width, const uint32 height);

			/*
				Texture operations.
			*/

			/// Sets texture parameter to texture
			/// This function assumes the texture is binded already 
			void setTextureParameter(const TextureTarget target, const TextureParameterName field, int value);

			void setTextureData(const TextureTarget target,
								const int level,
								const SurfaceFormat internalFormat,
								const int width,
								const int height,
								const SurfaceFormat format,
								const unsigned char* data);

			void getTextureData(const TextureTarget target, const int level, const SurfaceFormat format, unsigned char* data);
			void deleteTexture(const uint32 texture);

			/*
				Shader operations.
			*/

			/// Attempts to compile given shader source
			/// @param[in] shader result shader
			/// @param[in] source source code of the shader
			void compileShader(uint32& shader, const char* source, const ShaderType type);

			/// Deletes the given shader.
			void deleteShader(const uint32 shader);

			/// Creates new shader program.
			void createProgram(uint32& program);
			/// Links given shader to given program.
			/// @param[in] program program where the shader is linked to
			/// @param[in] shader shader to be linked with the program
			/// @param[in] dispose should the shader be deleted after it has been linked with the program
			void linkToProgram(const uint32 program, const uint32 shader, const bool dispose);
			/// Links the given program.
			void linkProgram(const uint32 program);

			/// Uses the given program. Passing 0 to this function
			/// means the current program will be unbinded.
			void useProgram(const uint32 program);
			
			/// Sets the given shader uniform.
			/// @param[in] shader program that contains the uniform to set
			/// @param[in] name name of the uniform
			/// @param[in] data data to be inserted in the uniform location
			void setShaderUniform(const uint32 shader, const char* name, void* data, const UniformType type);

			int32 getUniformsCount(const uint32 shader) const;

			int32 getUniformLocation(const uint32 shader, const String& name) const;

			void getUniformInformation(const uint32 shader, const int32 index, int32& location, String& name, uint32& type, int32& valuesCount) const;

			/*
				Buffer operations.
			*/

			/// Generates a buffer.
			void generateBuffer(uint32& buffer);
			/// Binds given buffer.
			void bindBuffer(uint32& buffer, const BufferType type);
			/// Unbinds given type buffer.
			void unbindBuffer(const BufferType type);
			/// Sets given buffers data.
			void setBufferData(const BufferType type, const uint32 bytes, void* data, const BufferUsage usage);
			void setBufferSubData(const BufferType type, const uint32 offset, const uint32 bytes, void* data);
			void deleteBuffer(const uint32 buffer);

			void drawArrays(const RenderMode mode, const uint32 first, const uint32 last);
			void drawElements(const RenderMode mode, const PrimitiveType type, const uint32 count, const uint32 indices);

			void createVertexAttributePointer(const VertexAttributePointerDescription& description);
			void disableVertexAttributePointer(const uint32 location);

			void bindAttributeLocation(const uint32 shader, const uint32 index, const String& name);

			/*
				State operations.
			*/

			/// Saves the current state of the device.
			/// State data that will be stored for later use contains:
			/// - viewport
			/// - texture
			/// - render target
			/// - shader
			/// - binded buffers
			/// - vertex attributes
			void saveState();

			/// Resumes the last state of the device.
			void resumeState();

			/// Returns the current states ID to the caller. 
			/// If this functions returns 1 the device
			/// is in it's primary state.
			uint32 currentState() const;

			~GraphicsDevice();
		};
	}
}