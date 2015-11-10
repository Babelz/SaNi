#include "sani/graphics/renderables/triangle.hpp"
#include "sani/graphics/buffer.hpp"

namespace sani {

	namespace graphics {

		/*
					tx/ty
					/   \
				   /	 \
				  /       \
				 /         \
				/           \
			  lx/ly_______rx/ry
		*/

		/*
			0-2 = border vertices.
			3-5 = shape vertices.
		*/

		Triangle::Triangle(const float32 tx, const float32 ty, const float32 lx, const float32 ly, const float32 rx, const float32 ry) : Renderable(6, 2),
																																		 fill(color::red),
																																		 borderFill(color::green),
																																		 borderThickness(0.0f) {
			topPoint.x = tx;
			topPoint.y = ty;
			VertexPositionColorTexture& topVertex = renderData.vertices[3];
			topVertex.textureCoordinates.x = 0.5f;
			topVertex.textureCoordinates.y = 1.0f;

			leftPoint.x = lx;
			leftPoint.y = ly;
			VertexPositionColorTexture& leftVertex = renderData.vertices[4];
			leftVertex.textureCoordinates.x = 0.0f;
			leftVertex.textureCoordinates.y = 1.0f;

			rightPoint.x = rx;
			rightPoint.y = ry;
			VertexPositionColorTexture& rightVertex = renderData.vertices[5];
			rightVertex.textureCoordinates.x = 1.0f;
			rightVertex.textureCoordinates.y = 1.0f;

			transform.origin.x = localBounds.w / 2.0f;
			transform.origin.x = localBounds.h / 2.0f;

			transform.position.x = rx;
			transform.position.y = ty;

			recomputeGeometryData(*this);
			updateRenderData(*this);

			RenderElementData& shapeRenderData = renderData.renderElements[0];
			shapeRenderData.first = 3;
			shapeRenderData.last = 5;
			shapeRenderData.vertexElements = 7;		// TODO: no texturing.
			shapeRenderData.offset = 2;

			RenderElementData& borderRenderData = renderData.renderElements[1];
			borderRenderData.first = 0;
			borderRenderData.last = 2;
			borderRenderData.vertexElements = 7;
			borderRenderData.offset = 2;
		}
		Triangle::Triangle(const sani::math::Vec2f& top, const sani::math::Vec2f& left, const sani::math::Vec2f& right) 
			: Triangle(top.x, top.y, left.x, left.y, right.x, right.y) {
		}
		Triangle::Triangle(const float32 x, const float32 y, const float32 width, const float32 height) 
			: Triangle(x + width / 2.0f, y, x, y + height, x + width, y + height) {
		}
		Triangle::Triangle(const sani::math::Vec2f& position, const sani::math::Vec2f& size) 
			: Triangle(position.x - size.x / 2.0f, position.y, position.x, position.y + size.y, position.x + size.x, position.y + size.y) {
		}
		Triangle::Triangle(const float32 width, const float32 height) 
			: Triangle(width / 2.0f, 0.0f, 0.0f, height, width, height) {
		}
	}
}