#pragma once

#include "sani/platform/platform_config.hpp"
#include "sani/types.hpp"
#include "sani/platform/graphics/texture.hpp"

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
			uint32 framebuffer;
			uint32 colorBuffer;
			uint32 depthBuffer;
		public:
			/// Creates new instance of the rendertarget class, generates 
			/// all required buffers for it and initializes it.
			RenderTarget2D(GraphicsDevice* device, const uint32 width, const uint32 height);
			
			/// Returns the color buffer.
			uint32 getColorBuffer() const;
			/// Returns the depth buffer.
			uint32 getDepthBuffer() const;
			uint32 getFramebuffer() const;
		};
	}
}