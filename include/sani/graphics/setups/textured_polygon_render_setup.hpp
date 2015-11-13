#pragma once

#include "sani/graphics/setups/polygon_render_setup.hpp"

namespace sani {

	namespace graphics {

		class TexturedPolygonRenderSetup : public PolygonRenderSetup {
		private:
			uint32 texture;
		public:
			TexturedPolygonRenderSetup(GraphicsDevice* const graphicsDevice);

			void setTexture(const uint32 texture);
			uint32 getTexture() const;

			virtual void use() override;
			
			virtual void clear() override;
		};
	}
}