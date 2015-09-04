#include "sani/platform/texture.hpp"

namespace sani {
	namespace graphics {

		Texture::Texture(GraphicsDevice& device, const uint32 width, const uint32 height) : width(width),
																							height(height) {
			// Generate new, empty texture.
			device.generateTexture(renderTexture, width, height);
		}

		uint32 Texture::getID() const {
			return renderTexture;
		}

		uint32 Texture::getWidth() const {
			return width;
		}
		uint32 Texture::getHeight() const {
			return height;
		}
	}
}