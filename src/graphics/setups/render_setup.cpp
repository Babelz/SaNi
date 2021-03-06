#include "sani/platform/graphics/graphics_device.hpp"
#include "sani/graphics/setups/render_setup.hpp"

namespace sani {
	namespace graphics {

		RenderSetup::RenderSetup(GraphicsDevice* const graphicsDevice) : graphicsDevice(graphicsDevice) {
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