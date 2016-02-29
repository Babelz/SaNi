#pragma once

#include "sani/platform/platform_config.hpp"
#include "sani/platform/graphics/texture.hpp"
#include "sani/types.hpp"

namespace sani {

	namespace graphics {

		class GraphicsDevice;
		
		/// @class RenderTarget2D "sani/platform/rendertarget.h"
		/// @author voidbab
		/// 
		/// Represents a two dimensional render target, which uses 32-bit ARGB surface format.
		class RenderTarget2D final : public Texture {
		private:
			uint32 framebuffer;
		protected:
			virtual bool onDispose() override;
		public:
			/// Creates new instance of the render target class, generates 
			/// all required buffers for it and initializes it.
			RenderTarget2D(GraphicsDevice* device, const uint32 width, const uint32 height);

			uint32 getFramebuffer() const;
			
			~RenderTarget2D() = default;
		};
	}
}