#pragma once

#include "sani/forward_declare.hpp"
#include "sani/platform/graphics/graphics_error.hpp"
#include "sani/platform/graphics/graphics_enums.hpp"
#include "sani/platform/platform_config.hpp"
#include "sani/core/events.hpp"

#include <stack>

#if SANI_TARGET_PLATFORM == SANI_PLATFORM_WINDOWS

#include <Windows.h>

#endif

SANI_FORWARD_DECLARE_2(sani, graphics, RenderTarget2D);
SANI_FORWARD_DECLARE_2(sani, graphics, Texture);

SANI_FORWARD_DECLARE_STRUCT_2(sani, graphics, Viewport);
SANI_FORWARD_DECLARE_STRUCT_2(sani, graphics, TextureDescription);
SANI_FORWARD_DECLARE_STRUCT_2(sani, graphics, VertexAttributePointerDescription);
SANI_FORWARD_DECLARE_STRUCT_2(sani, graphics, BufferDescription);

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
		
		using ErrorBuffer = std::stack<GraphicsError>;

		struct Impl;

		/// @class GraphicsDevice graphics_device.hpp "sani/platform/graphics_device.hpp"
		/// @author voidbab
		/// 
		/// A virtual representation of the physical graphics adapter of this machine.
		class GraphicsDevice {
		private:
			ErrorBuffer errorBuffer;
			
			Impl* impl;

			bool createContext();
			bool initializeGlew();
			bool initializeDevice();
			
			void setupScreenShader();

			void pushError(const String& message, const char* const fnc, const uint32 ln);
			void checkForAPIErrors(const char* const fnc, const uint32 ln);

			uint32 compileShader(const char* const src, const ShaderType type, String& error);
		public:
			SANI_DECLARE_EVENT(backbufferSizeChanged, void(const uint32, const uint32, const uint32, const uint32));
			SANI_DECLARE_EVENT(viewportSizeChanged, void(const Viewport&, const Viewport&));

			GraphicsDevice(const HWND hWnd, const HINSTANCE hInstance);
			
			void initialize(const int32 backBufferWidth, const int32 backBufferHeight, const uint32 samples);
			void dispose();

			GraphicsError nextError();
			bool hasErrors();

			// Display related.
			bool isFullscreen() const;
			void fullscreen();
			void windowed();

			// Backbuffer/rt related.
			void setBackbufferSize(const uint32 width, const uint32 height);
			uint32 getBackbufferWidth() const;
			uint32 getBackbufferHeight() const;

			void setSamplesCount(const uint32 samples);
			uint32 getSamplesCount() const;

			void applyBackbufferChanges();

			void setRenderTarget(RenderTarget2D* const renderTarger);

			// Viewport related.
			void setViewport(const Viewport& viewport);
			const Viewport& getViewport() const;

			// Buffer related.
			uint32 createBuffer(const BufferDescription* const desc);
			void deleteBuffer(const uint32 id);
			void bindBuffer(const BufferType target, const uint32 id);
			void setBufferData(const BufferType target, const void* const data, const uint32 bytes, const uint32 offset = 0);
			
			// Texture related.
			void bindTexture(const TextureTarget target, const uint32 id);
			uint32 createTexture(const TextureDescription* const desc);

			void createRendertarget(uint32& txid, uint32& fbid, const uint32 width, const uint32 height, const uint32 samples = 0);
			void deleteRenderTarget(const uint32 fbid);

			void setTextureParameter(const TextureTarget target, const TextureParameterName field, const int32 value);
			void getTextureData(const TextureTarget target, const int32 level, const SurfaceFormat format, unsigned char* data);
			void setTextureData(const TextureTarget target,
								const int32 level,
								const SurfaceFormat internalFormat,
								const int32 width,
								const int32 height,
								const SurfaceFormat format,
								const unsigned char* data);

			void deleteTexture(const uint32 texid);

			// Effect related.
			void bindEffect(const uint32 id);

			int32 getUniformsCount();
			int32 getUniformLocation(const String& name);
			
			void getUniformInformation(const uint32 index, uint32& location, String& name, uint32& type, int32& valuesCount);
			void setUniformValue(const String& name, const void* const data, const UniformType type);

			uint32 compileEffect(const char* const vscr, const char* const fscr, String& errors);
			uint32 compileEffect(const char* const vscr, const char* const fscr);
			void deleteEffect(const uint32 id);

			// Vertex pointer related.
			void createVertexPointer(const VertexAttributePointerDescription* const desc);
			void disableVertexPointer(const uint32 location);

			// Drawing related.
			void clear(const float32 r, const float32 g, const float32 b, const float32 a);
			void present(const uint32 effect);
			void drawArrays(const RenderMode mode, const uint32 first, const uint32 last);
			void drawElements(const RenderMode mode, const PrimitiveType type, const uint32 count, const uint32 indices);
			
			// State functions.
			void resumeState();
			void saveState();

			~GraphicsDevice();
		};
	}
}