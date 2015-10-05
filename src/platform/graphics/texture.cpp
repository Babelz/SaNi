#include "sani/platform/graphics/texture.hpp"

namespace sani {
	namespace graphics {

		Texture::Texture(GraphicsDevice& device, const uint32 width, const uint32 height) : width(width),
																							height(height),
																							renderTexture(0) {
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