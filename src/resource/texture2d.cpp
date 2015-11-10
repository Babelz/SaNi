#include "sani/resource/texture2d.hpp"
#include "sani/platform/graphics/graphics_device.hpp"

namespace sani {
	namespace resource {
		Texture2D::Texture2D(graphics::GraphicsDevice* device, const uint32 width, const uint32 height, const GLuint id)
			: Texture(device, width, height) {
			// TODO hax
			renderTexture = id;
		}

		Texture2D::~Texture2D() {}
	}
}