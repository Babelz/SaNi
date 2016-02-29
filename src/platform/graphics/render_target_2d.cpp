#include "sani/platform/graphics/graphics_device.hpp"
#include "sani/platform/graphics/render_target_2d.hpp"

namespace sani {

	namespace graphics {

		RenderTarget2D::RenderTarget2D(GraphicsDevice* device, const uint32 width, const uint32 height) : Texture(device, width, height),
																										  framebuffer(0) {
			uint32 id = 0;
			device->generateRenderTarget2D(id, framebuffer, width, height);
			
			setID(id);
		}

		bool RenderTarget2D::onDispose() {
			GraphicsDevice* const device = getDevice();

			device->deleteTexture(getID());
			device->deleteFramebuffer(framebuffer);

			return device->hasErrors();
		}

		uint32 RenderTarget2D::getFramebuffer() const {
			return framebuffer;
		}
	}
}