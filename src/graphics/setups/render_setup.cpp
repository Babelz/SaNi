#include "sani/platform/graphics/graphics_device.hpp"
#include "sani/graphics/setups/render_setup.hpp"

namespace sani {
	namespace graphics {

		RenderSetup::RenderSetup(GraphicsDevice* const graphicsDevice) : graphicsDevice(graphicsDevice) {
		}
		RenderSetup::RenderSetup() : graphicsDevice(nullptr) {
		}

		void RenderSetup::setRenderMode(const RenderMode renderMode) {
			this->renderMode = renderMode;
		}
		RenderMode RenderSetup::getRenderMode() const {
			return renderMode;
		}

		void RenderSetup::setElements(const uint32 elements) {
			this->elements = elements;
		}
		uint32 RenderSetup::getElements() const {
			return elements;
		}

		GraphicsDevice* const RenderSetup::getGraphicsDevice() const {
			return graphicsDevice;
		}
		
		RenderSetup::~RenderSetup() {
		}
	}
}