#include "sani/graphics/renderables/rectangle.hpp"
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

			VertexPositionColorTexture& topLeftVertex = renderData.vertices[0];
			topLeftVertex.textureCoordinates.x = 0.0f;
			topLeftVertex.textureCoordinates.y = 1.0f;

			VertexPositionColorTexture& topRightVertex = renderData.vertices[1];
			topRightVertex.textureCoordinates.x = 1.0f;
			topRightVertex.textureCoordinates.y = 1.0f;

			VertexPositionColorTexture& bottomLeftVertex = renderData.vertices[2];
			bottomLeftVertex.textureCoordinates.x = 0.0f;
			bottomLeftVertex.textureCoordinates.y = 0.0f;

			VertexPositionColorTexture& bottomRightVertex = renderData.vertices[3];
			bottomRightVertex.textureCoordinates.x = 1.0f;
			bottomRightVertex.textureCoordinates.y = 0.0f;

			transform.position.x = x;
			transform.position.y = y;
			transform.origin.x = localBounds.w / 2.0f;
			transform.origin.y = localBounds.h / 2.0f;

			recomputeGeometryData(*this);
			updateRenderData(*this);

			RenderElementData& shapeRenderData = renderData.renderElements[0];
			shapeRenderData.first = 0;
			shapeRenderData.last = 3;
			shapeRenderData.vertexElements = 7;		// TODO: no texturing.
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

			updateGroupIdentifier(*this);
		}
		Rectangle::Rectangle(const sani::math::Vec2f& position, const sani::math::Vec2f& size) : Rectangle(position.x, position.y, size.x, size.y) {
		}
		Rectangle::Rectangle() : Rectangle(0.0f, 0.0f, 1.0f, 1.0f) {
		}
	}
}