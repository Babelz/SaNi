#include "sani/platform/graphics/graphics_device.hpp"
#include "sani/platform/graphics/render_target_2d.hpp"

namespace sani {

	namespace graphics {

		RenderTarget2D::RenderTarget2D(GraphicsDevice* device, const uint32 width, const uint32 height) : Texture(device, width, height),
																										  framebuffer(0) {
			device->generateRenderTarget2D(renderTexture, framebuffer, width, height);
		}

		RenderTarget2D::RenderTarget2D() : Texture(),
										   framebuffer(0) {
		}

		uint32 RenderTarget2D::getFramebuffer() const {
			return framebuffer;
		}

		bool RenderTarget2D::empty() const {
			return framebuffer == 0 && renderTexture == 0;
		}

		RenderTarget2D::~RenderTarget2D() {
			if (framebuffer != 0) {
				getDevice()->deleteBuffer(framebuffer);
				
				getDevice()->deleteTexture(getID());
			}
		}
	}
}