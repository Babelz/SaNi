#include "sani/platform/graphics/graphics_device.hpp"
#include "sani/graphics/renderer.hpp"

namespace sani {

	namespace graphics {

		Renderer::Renderer(GraphicsDevice* graphicsDevice) : graphicsDevice(graphicsDevice) {
		}

		bool Renderer::initialize() {
			return true;
		}

		void Renderer::renderPrimitives(PrimitiveComponentList& components) {
		}

		void Renderer::begin() {
		}
		void Renderer::end() {
		}
	}
}