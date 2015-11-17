#pragma once

#include "sani/graphics/setups/polygon_render_setup.hpp"

namespace sani {

	namespace graphics {

		class TexturedPolygonRenderSetup : public PolygonRenderSetup {
		public:
			TexturedPolygonRenderSetup(GraphicsDevice* const graphicsDevice);

			virtual void use() override;
			
			virtual void clear() override;
		};
	}
}