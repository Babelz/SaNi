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

		void RenderSetup::setVertexElementsCount(const uint32 vertexElementsCount) {
			this->vertexElementsCount = vertexElementsCount;
		}
		uint32 RenderSetup::getVertexElementsCount() const {
			return vertexElementsCount;
		}

		GraphicsDevice* const RenderSetup::getGraphicsDevice() const {
			return graphicsDevice;
		}
		
		RenderSetup::~RenderSetup() {
		}
	}
}