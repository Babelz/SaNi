#include "sani/platform/graphics/graphics_device.hpp"
#include "sani/platform/graphics/render_target_2d.hpp"

namespace sani {

	namespace graphics {

		RenderTarget2D::RenderTarget2D(GraphicsDevice* device, const uint32 width, const uint32 height) : Texture(device, width, height),
																										  framebuffer(0),
																										  colorBuffer(0),
																										  depthBuffer(0) {

			TextureDescription description;
			description.format = SurfaceFormat::ColorRGBA;
			description.height = height;
			description.width = width;
			description.levels = 1;

			device->generateTexture(renderTexture, description);
			device->generateRenderTarget2D(renderTexture, colorBuffer, framebuffer, depthBuffer, width, height);
		}

		uint32 RenderTarget2D::getColorBuffer() const {
			return colorBuffer;
		}
		uint32 RenderTarget2D::getDepthBuffer() const {
			return depthBuffer;
		}
		uint32 RenderTarget2D::getFramebuffer() const {
			return framebuffer;
		}
	}
}