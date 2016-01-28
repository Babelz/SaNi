#pragma once

#include "sani/platform/platform_config.hpp"
#include "sani/types.hpp"
#include "sani/platform/graphics/texture.hpp"

namespace sani {

	namespace graphics {

		class GraphicsDevice;
		
		/// @class RenderTarget2D "sani/platform/rendertarget.h"
		/// @author voidbab
		/// 
		/// Represents a two dimensional render target, which uses 32-bit ARGB surface format.
		class RenderTarget2D : public Texture {
		private:
			uint32 framebuffer;
		public:
			/// Creates new instance of the render target class, generates 
			/// all required buffers for it and initializes it.
			RenderTarget2D(GraphicsDevice* device, const uint32 width, const uint32 height);
			
			uint32 getFramebuffer() const;
			
			~RenderTarget2D();
		};
	}
}