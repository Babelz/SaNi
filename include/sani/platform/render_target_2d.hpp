#pragma once

#include "sani/platform/platform_config.hpp"
#include "sani/precompiled.hpp"
#include "sani/platform/texture.hpp"

/*
	TODO: inherit from Texture when it has been implemented.
*/

namespace sani {
	namespace graphics {

		class GraphicsDevice;
		
		/// @class RenderTarget2D "sani/platform/rendertarget.h"
		/// @author voidbab
		/// 
		/// Represents a two dimensional rendertarget, wich uses 32-bit ARGB surface format.
		class RenderTarget2D : public Texture {
		private:
			Buffer framebuffer;
			Buffer colorBuffer;
			Buffer depthBuffer;
		public:
			/// Creates new instance of the rendertarget class, generates 
			/// all required buffers for it and initializes it.
			RenderTarget2D(GraphicsDevice& device, const uint32 width, const uint32 height);
			
			/// Returns the color buffer.
			Buffer getColorBuffer() const;
			/// Returns the depth buffer.
			Buffer getDepthBuffer() const;
			Buffer getFramebuffer() const;
		};
	}
}