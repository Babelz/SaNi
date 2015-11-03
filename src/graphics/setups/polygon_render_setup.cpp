#include "sani/platform/graphics/graphics_precompiled.hpp"
#include "sani/graphics/setups/polygon_render_setup.hpp"
#include "sani/platform/graphics/graphics_device.hpp"
#include "sani/types.hpp"

namespace sani {

	namespace graphics {

		PolygonRenderSetup::PolygonRenderSetup(GraphicsDevice* const graphicsDevice) : RenderSetup(graphicsDevice) {
			setRenderMode(RenderMode::Triangles);
		}

		void PolygonRenderSetup::use() {
			VertexAttributePointerDescription vertexDescription;
			vertexDescription.location = 0;
			vertexDescription.count = 3;
			vertexDescription.type = PrimitiveType::Float;
			vertexDescription.normalized = false;
			vertexDescription.stride = sizeof(float32) * getElements();
			vertexDescription.offset = 0;
			
			VertexAttributePointerDescription colorDescription;
			colorDescription.location = 1;
			colorDescription.count = 4;
			colorDescription.type = PrimitiveType::Float;
			colorDescription.normalized = false;
			colorDescription.stride = sizeof(float32) * getElements();
			colorDescription.offset = sizeof(float32) * 3;

			GraphicsDevice* const graphicsDevice = getGraphicsDevice();
			graphicsDevice->createVertexAttributePointer(vertexDescription);
			graphicsDevice->createVertexAttributePointer(colorDescription);
		}

		void PolygonRenderSetup::clear() {
			GraphicsDevice* const graphicsDevice = getGraphicsDevice();
			graphicsDevice->disableVertexAttributePointer(0);
			graphicsDevice->disableVertexAttributePointer(1);
			
			setRenderMode(RenderMode::Triangles);
		}
	}
}