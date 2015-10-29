#include "sani/platform/graphics/graphics_device.hpp"
#include "sani/graphics/renderer.hpp"

namespace sani {

	namespace graphics {

		Renderer::Renderer(GraphicsDevice* graphicsDevice) : graphicsDevice(graphicsDevice) {
		}

		Renderer::~Renderer() {
		}
	}
}