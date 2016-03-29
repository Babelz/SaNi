#include "sani/platform/graphics/graphics_enums.hpp"
#include "sani/graphics/setups/polygon_render_setup.hpp"
#include "sani/platform/graphics/graphics_device.hpp"
#include "sani/platform/graphics/descriptions.hpp"
#include "sani/types.hpp"

namespace sani {

	namespace graphics {

		const uint32 VtxLocation = 0;
		const uint32 ColorLocation = 1;

		PolygonRenderSetup::PolygonRenderSetup(GraphicsDevice* const graphicsDevice) : RenderSetup(graphicsDevice) {
		}

		void PolygonRenderSetup::use() {
			VertexAttributePointerDescription vertexDescription;
			vertexDescription.location = VtxLocation;
			vertexDescription.size = 3;
			vertexDescription.type = PrimitiveType::Float;
			vertexDescription.normalized = false;
			vertexDescription.stride = sizeof(float32) * getVertexElementsCount();
			vertexDescription.offset = 0;
			
			VertexAttributePointerDescription colorDescription;
			colorDescription.location = ColorLocation;
			colorDescription.size = 4;
			colorDescription.type = PrimitiveType::Float;
			colorDescription.normalized = false;
			colorDescription.stride = sizeof(float32) * getVertexElementsCount();
			colorDescription.offset = sizeof(float32) * 3;

			GraphicsDevice* const graphicsDevice = getGraphicsDevice();
			graphicsDevice->createVertexPointer(&vertexDescription);
			graphicsDevice->createVertexPointer(&colorDescription);
		}

		void PolygonRenderSetup::clear() {
			GraphicsDevice* const graphicsDevice = getGraphicsDevice();
			graphicsDevice->disableVertexPointer(VtxLocation);
			graphicsDevice->disableVertexPointer(ColorLocation);
		}
	}
}