#include "sani/graphics/setups/render_setup.hpp"
#include "sani/graphics/renderer.hpp"

namespace sani {
	
	namespace graphics {

		/// Returns the current render state.
		RenderState Renderer::getRenderState() const {
			return renderState;
		}
		/// Returns the current vertex mode.
		VertexMode Renderer::getVertexMode() const {
			return vertexMode;
		}
		/// Returns the current render mode.
		RenderMode Renderer::getRenderMode() const {
			return renderSetup->getRenderMode();
		}

		/// Returns the count of elements each vertex should have.
		uint32 Renderer::getVertexElementsCount() const {
			return renderSetup->getVertexElementsCount();
		}
	}
}