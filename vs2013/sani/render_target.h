#pragma once

#include "sani/platform/platform_config.hpp"
#include "sani/precompiled.hpp"

namespace sani {
	namespace graphics {

		class GraphicsDevice;

		/// @class RenderTarget2D "sani/platform/rendertarget.h"
		/// @author voidbab
		/// 
		/// Represents a two dimensional rendertarget, wich uses 32-bit ARGB surface format.
		class RenderTarget2D {
		private:
			class Impl;

			Impl* impl;

			uint32 stencilBuffer;
			uint32 colorBuffer;
			uint32 depthBuffer;

			const uint16 width;
			const uint16 height;
		
			void initialize(GraphicsDevice& device);
		public:
			RenderTarget2D(GraphicsDevice& device, const uint16 width, const uint16 height);

			/// Returns the width of the rendertarget.
			uint16 getWidth() const;
			/// Returns the height of the rendertarget.
			uint16 getheight() const;

			/// Returns the stencil buffer.
			uint32 getStencilBuffer() const;
			/// Returns the color buffer.
			uint32 getColorBuffer() const;
			/// Returns the depth buffer.
			uint32 getDepthBuffer() const;
		};
	}
}