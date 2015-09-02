#pragma once
#include "sani/platform/graphics_precompiled.hpp"
#include "sani/platform/platform_config.hpp"

#include <stack>

#if SANI_TARGET_PLATFORM == SANI_PLATFORM_WIN32

#include <Windows.h>

#endif

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
		
		typedef std::stack<uint32> ErrorBuffer;

		// Forward declarations.
		struct Color;
		struct Viewport;
		class RenderTarget2D;

		/// @class GraphicsDevice graphics_device.hpp "sani/platform/graphics_device.hpp"
		/// @author voidbab
		/// 
		/// A virtual representation of the physical graphics adapter of this machine.
		/// DX contains WinDX and GL contains Linux and WinGL implementations.
		class GraphicsDevice {
		private:
			class Impl;

			Impl* impl;

			ErrorBuffer errorBuffer;

			void checkForErrors();
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
			uint32 getError();

			/// Sets the viewport of the device.
			/// @param[in] viewport viewport to use
			void setViewport(const Viewport& viewport);
			/// Returns the current viewport to the user.
			const Viewport& getViewport() const;

			/// Initializes the device.
			bool initialize();
			/// Cleans the device.
			bool cleanUp();

			/// Applies all changes done to the device.
			bool applyChanges();

			/// Clears the device.
			void clear(const Color& color);
			/// Draws all contents of the device.
			void present();

			/*
				Texture and render target operations.
			*/

			void bindTexture(const RenderTexture texture);
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

			void compileShader(Shader& shader, const char* source);
			void bindShader(const Shader shader);
			void unbindShader(const Shader shader);
			void setShaderUniform(const Shader shader, const char* name, void* data);

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

