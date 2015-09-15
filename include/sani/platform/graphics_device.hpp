#pragma once
#include "sani/platform/graphics_error.hpp"
#include "sani/platform/graphics_precompiled.hpp"
#include "sani/platform/platform_config.hpp"

#include <stack>

#if SANI_TARGET_PLATFORM == SANI_PLATFORM_WIN32

#include <Windows.h>

#endif

#define CHECK_FOR_ERRORS() checkForErrors(__FUNCTION__, __LINE__)

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
		*/
		
		// Forward declarations.
		struct Color;
		struct Viewport;
		
		class RenderTarget2D;
		
		typedef std::stack<GraphicsError> ErrorBuffer;

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
		public:

			// Public Win32 members.
#if SANI_TARGET_PLATFORM == SANI_PLATFORM_WIN32

			GraphicsDevice(const HWND hWnd, const HINSTANCE hInstance, const int32 backBufferWidth, const int32 backBufferHeight);

			bool isFullscreen() const;
			void setFullscreen();
			void setWindowed();
#endif
			/// Returns the width of the back buffer.
			uint32 getBackBufferWidth() const;
			/// Returns the height of the back buffer.
			uint32 getBackBufferHeight() const;

			// Sets the width of the back buffer.
			void setBackBufferWidth(const uint32 newWidth);
			/// Sets the height of the back buffer.
			void setBackBufferHeight(const uint32 newHeight);

			/// Returns true if the error buffer contains errors.
			bool hasErrors() const;
			/// Returns the next error from the error buffer.
			GraphicsError getError();

			/// Sets the viewport of the device.
			/// @param[in] viewport viewport to use
			void setViewport(const Viewport& viewport);
			/// Returns the current viewport to the user.
			const Viewport& getViewport() const;

			/// Initializes the device.
			bool initialize();
			/// Cleans the device.
			bool cleanUp();

			/// Clears the device. Swaps the back
			/// and front buffer.
			void clear(const Color& color);
			/// Draws all contents of the device.
			void present();

			/*
				Texture and render target operations.
			*/

			/// Binds given texture.
			/// @param[in] texture texture to bind
			void bindTexture(const RenderTexture texture);
			/// Unbinds current texture.
			void unbindTexture();
			
			/// Sets the current render target for the device.
			/// If the value is null, default render target
			/// will be used.
			void setRenderTarget(RenderTarget2D* renderTarget);

			/// Creates an empty RGBA color-format texture.
			void generateTexture(RenderTexture& texture, const uint32 width, const uint32 height);
			/// Generates new render target.
			/// @param[in] renderTexture texture to be used with the target, call generateTexture before passing it
			/// @param[in] colorBuffer color buffer to be generated for the target
			/// @param[in] frameBuffer frame buffer to be generated for the target
			/// @param[in] depthBuffer depth buffer to be generated for the target
			/// @param[in] width width of the render target
			/// @param[in] height of the render target
			void generateRenderTarget2D(RenderTexture& texture, Buffer& colorBuffer, Buffer& frameBuffer, Buffer& depthBuffer, const uint32 width, const uint32 height);

			/*
				Shader operations.
			*/
			
			/// Attempts to compile given shader source
			/// @param[in] shader result shader
			/// @param[in] source source code of the shader
			void compileShader(Shader& shader, const char* source, const ShaderType type);

			/// Deletes the given shader.
			void deleteShader(const Shader shader);

			/// Creates new shader program.
			void createProgram(ShaderProgram& program);
			/// Links given shader to given program.
			/// @param[in] program program where the shader is linked to
			/// @param[in] shader shader to be linked with the program
			/// @param[in] dispose should the shader be deleted after it has been linked with the program
			void linkToProgram(const ShaderProgram program, const Shader shader, const bool dispose);
			/// Links the given program.
			void linkProgram(const ShaderProgram program);

			/// Uses the given program. Passing 0 to this function
			/// means the current program will be unbinded.
			void useProgram(const ShaderProgram program);
			
			/// Sets the given shader uniform.
			/// @param[in] shader program that contains the uniform to set
			/// @param[in] name name of the uniform
			/// @param[in] data data to be inserted in the uniform location
			void setShaderUniform(const ShaderProgram shader, const char* name, void* data, const UniformType type);

			/*
				Buffer functions.
			*/

			void generateVertexArray(Buffer& vertexArray);
			void bindVertexArray(Buffer& buffer);

			void generateBuffer(Buffer& buffer, const BufferType type);
			void bindElementBuffer(Buffer& buffer, const BufferType type);
			void setElementBufferData(Buffer& buffer, const uint32 bytes, void* data, const ElementBufferUsage usage);

			void drawElements(const uint32 count, const IndicesType type, const uint32 indices);

			~GraphicsDevice();
		};
	}
}

