#include "sani/graphics/renderables/rectangle.hpp"
#include "sani/graphics/vertex_helper.hpp"
#include "sani/graphics/renderer.hpp"

namespace sani {

	namespace graphics {

		/*
				tl------tr
				|  \    |
				|   \   |
				|    \  |
				bl------br
		*/

		Rectangle::Rectangle(const float32 x, const float32 y, const float32 w, const float32 h) : Renderable(8, 6, 2) {
			fill = color::red;
			borderFill = color::green;

			borderThickness = 0.0f;

			localBounds.w = w;
			localBounds.h = h;

			VertexPositionColorTexture* vertices[] {
				&renderData.vertices[0],
				&renderData.vertices[1],
				&renderData.vertices[2],
				&renderData.vertices[3]
			};

			applyDefaultRectangleTextureCoordinates(vertices);
			
			transform.position.x = x;
			transform.position.y = y;
			transform.origin.x = localBounds.w / 2.0f;
			transform.origin.y = localBounds.h / 2.0f;

			RenderElementData& shapeRenderData = renderData.renderElements[0];
			shapeRenderData.first = 0;
			shapeRenderData.last = 3;
			shapeRenderData.vertexElements = 7;		
			shapeRenderData.offset = 2;
			shapeRenderData.indices = 6;

			RenderElementData& borderRenderData = renderData.renderElements[1];
			borderRenderData.first = 4;
			borderRenderData.last = 7;
			borderRenderData.vertexElements = 7;
			borderRenderData.offset = 2;
			borderRenderData.indices = 6;

			renderData.vertexIndices[0] = 0;
			renderData.vertexIndices[1] = 1;
			renderData.vertexIndices[2] = 2;

			renderData.vertexIndices[3] = 1;
			renderData.vertexIndices[4] = 3;
			renderData.vertexIndices[5] = 2;

			recomputeBounds(*this);
			recomputeVertices(*this);
			updateRenderData(*this);
		}
		Rectangle::Rectangle(const math::Vec2f& position, const math::Vec2f& size) : Rectangle(position.x, position.y, size.x, size.y) {
		}
	}
}