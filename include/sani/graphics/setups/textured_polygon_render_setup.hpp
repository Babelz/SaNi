#pragma once

#include "sani/graphics/setups/polygon_render_setup.hpp"

namespace sani {

	namespace graphics {

		class TexturedPolygonRenderSetup final : public PolygonRenderSetup {
		public:
			TexturedPolygonRenderSetup(GraphicsDevice* const graphicsDevice);

			virtual void use() final override;
			
			virtual void clear() final override;
		};
	}
}