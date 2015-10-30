#include "sani/platform/graphics/graphics_device.hpp"
#include "sani/graphics/setups/render_setup.hpp"

namespace sani {
	namespace graphics {

		RenderSetup::RenderSetup(GraphicsDevice* const graphicsDevice) : graphicsDevice(graphicsDevice) {
		}
		RenderSetup::RenderSetup() : graphicsDevice(nullptr) {
		}

		GraphicsDevice* const RenderSetup::getGraphicsDevice() const {
			return graphicsDevice;
		}
		
		RenderSetup::~RenderSetup() {
		}
	}
}