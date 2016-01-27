#include "sani/platform/graphics/texture.hpp"
#include "sani/platform/graphics/graphics_device.hpp"

namespace sani {

	namespace graphics {

		Texture::Texture(GraphicsDevice* device, const uint32 width, const uint32 height) : width(width),
																							height(height),
																							renderTexture(0) {
		}

		Texture::~Texture() {
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

		bool Texture::operator ==(const Texture& lhs) const {
			return this->width == lhs.width &&
				   this->height == lhs.height &&
				   this->renderTexture == lhs.renderTexture;
		}
		bool Texture::operator !=(const Texture& lhs) const {
			return !(*this == lhs);
		}
	}
}