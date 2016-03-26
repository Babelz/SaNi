#include "sani/platform/graphics/graphics_device.hpp"
#include "sani/platform/graphics/render_target_2d.hpp"

namespace sani {

	namespace graphics {

		RenderTarget2D::RenderTarget2D(GraphicsDevice* device, const uint32 width, const uint32 height) : Texture(device, width, height),
																										  framebuffer(0),
																										  r(0.0f),
																										  g(0.0f),
																										  b(0.0f),
																										  a(0.0f) {
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

		float32 RenderTarget2D::getClearRed() const {
			return r;
		}
		float32 RenderTarget2D::getClearGreen() const {
			return g;
		}
		float32 RenderTarget2D::getClearBlue() const {
			return b;
		}
		float32 RenderTarget2D::getClearAlpha() const {
			return a;
		}

		void RenderTarget2D::setClearColor(const float32 r, const float32 g, const float32 b, const float32 a) {
			this->r = r;
			this->g = g;
			this->b = b;
			this->a = a;
		}
	}
}