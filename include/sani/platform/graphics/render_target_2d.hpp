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

			// Clear color values (r, g, b, a).
			float32 r;
			float32 g;
			float32 b;
			float32 a;
		protected:
			virtual bool onDispose() override;
		public:
			/// Creates new instance of the render target class, generates 
			/// all required buffers for it and initializes it.
			RenderTarget2D(GraphicsDevice* device, const uint32 width, const uint32 height, const uint32 samples = 0);

			uint32 getFramebuffer() const;

			float32 getClearRed() const;
			float32 getClearGreen() const;
			float32 getClearBlue() const;
			float32 getClearAlpha() const;

			void setClearColor(const float32 r, const float32 g, const float32 b, const float32 a);

			~RenderTarget2D() = default;
		};
	}
}