#pragma once

#include "sani/platform/graphics/graphics_precompiled.hpp"
#include "sani/graphics/setups/render_setup.hpp"
#include "sani/types.hpp"

namespace sani {

	namespace graphics {

		/// @class 
		class PolygonRenderSetup : public RenderSetup {
		public:
			PolygonRenderSetup(GraphicsDevice* const graphicsDevice);
			
			virtual void use() override;

			virtual void clear() override;
		};
	}
}