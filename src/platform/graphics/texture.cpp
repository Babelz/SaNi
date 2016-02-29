#include "sani/platform/graphics/texture.hpp"
#include "sani/platform/graphics/graphics_device.hpp"

namespace sani {

	namespace graphics {

		Texture::Texture(GraphicsDevice* device, const uint32 width, const uint32 height) : GraphicsResource(device),
																						    width(width),
																							height(height) {
		}

		bool Texture::onDispose() {
			GraphicsDevice* const device = getDevice();

			device->deleteTexture(getID());

			return device->hasErrors();
		}

		uint32 Texture::getWidth() const {
			return width;
		}
		uint32 Texture::getHeight() const {
			return height;
		}
	}
}