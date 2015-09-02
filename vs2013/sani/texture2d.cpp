#include "sani/platform/texture2d.h"

namespace sani {
	namespace graphics {

		Texture2D::Texture2D(GraphicsDevice& device, const uint32 width, const uint32 height) : width(width),
																							    height(height) {
			// Generate new, empty texture.
			device.generateTexture(renderTexture, width, height);
		}

		uint32 Texture2D::getID() const {
			return renderTexture;
		}

		uint32 Texture2D::getWidth() const {
			return width;
		}
		uint32 Texture2D::getHeight() const {
			return height;
		}
	}
}