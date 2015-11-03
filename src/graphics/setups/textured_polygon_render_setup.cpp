#include "sani/graphics/setups/textured_polygon_render_setup.hpp"
#include "sani/platform/graphics/graphics_device.hpp"

namespace sani {

	namespace graphics {

		TexturedPolygonRenderSetup::TexturedPolygonRenderSetup(GraphicsDevice* const graphicsDevice) : PolygonRenderSetup(graphicsDevice),
																									   texture(0) {
			// No need to set default render mode, base sets it.
		}

		void TexturedPolygonRenderSetup::setTexture(const uint32 texture) {
			this->texture = texture;
		}
		uint32 TexturedPolygonRenderSetup::getTexture() const {
			return texture;
		}

		void TexturedPolygonRenderSetup::use()  {
			PolygonRenderSetup::use();

			VertexAttributePointerDescription textureDescription;
			textureDescription.location = 2;
			textureDescription.count = 2;
			textureDescription.type = PrimitiveType::Float;
			textureDescription.normalized = false;
			textureDescription.stride = sizeof(float32) * getElements();
			textureDescription.offset = sizeof(float32) * 7;

			GraphicsDevice* const graphicsDevice = getGraphicsDevice();
			graphicsDevice->createVertexAttributePointer(textureDescription);
			graphicsDevice->bindTexture(texture);
		}

		void TexturedPolygonRenderSetup::clear() {
			PolygonRenderSetup::clear();

			GraphicsDevice* const graphicsDevice = getGraphicsDevice();
			graphicsDevice->disableVertexAttributePointer(2);
			graphicsDevice->unbindTexture();

			// No need to reset the render mode, base clears it.
		}
	}
}