#include "sani/graphics/setups/user_primitive_render_setup.hpp"
#include "sani/platform/graphics/graphics_precompiled.hpp"
#include "sani/platform/graphics/graphics_device.hpp"
#include "sani/types.hpp"

namespace sani {

	namespace graphics {

		UserPrimitiveRenderSetup::UserPrimitiveRenderSetup(GraphicsDevice* const graphicsDevice) : RenderSetup(graphicsDevice),
																								   renderMode(RenderMode::Triangles),
																								   vertices(0) {
		}

		void UserPrimitiveRenderSetup::setRenderMode(const RenderMode renderMode) {
			this->renderMode = renderMode;
		}
		RenderMode UserPrimitiveRenderSetup::getRenderMode() const {
			return renderMode;
		}

		void UserPrimitiveRenderSetup::setVertices(const uint32 vertices) {
			this->vertices = vertices;
		}
		uint32 UserPrimitiveRenderSetup::getVertices() const {
			return vertices;
		}

		void UserPrimitiveRenderSetup::use() {
			VertexAttributePointerDescription vertexDescription;
			vertexDescription.location = 0;
			vertexDescription.count = 3;
			vertexDescription.type = PrimitiveType::Float;
			vertexDescription.normalized = false;
			vertexDescription.stride = sizeof(float32) * vertices;
			vertexDescription.offset = 0;

			VertexAttributePointerDescription colorDescription;
			colorDescription.location = 1;
			colorDescription.count = 3;
			colorDescription.type = PrimitiveType::Float;
			colorDescription.normalized = false;
			colorDescription.stride = sizeof(float32) * vertices;
			colorDescription.offset = sizeof(float32) * 3;

			GraphicsDevice* const graphicsDevice = getGraphicsDevice();
			graphicsDevice->createVertexAttributePointer(vertexDescription);
			graphicsDevice->createVertexAttributePointer(colorDescription);
		}

		void UserPrimitiveRenderSetup::clear() {
			GraphicsDevice* const graphicsDevice = getGraphicsDevice();
			graphicsDevice->disableVertexAttributePointer(0);
			graphicsDevice->disableVertexAttributePointer(1);
		}
	}
}