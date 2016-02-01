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
			0-2 = shape vertices.
			3-5 = border vertices.
		*/

		Triangle::Triangle(const float32 tx, const float32 ty, const float32 lx, const float32 ly, const float32 rx, const float32 ry) : Renderable(6, 2),
																																		 fill(color::red),
																																		 borderFill(color::green),
																																		 borderThickness(0.0f) {
			topPoint.x = tx;
			topPoint.y = ty;
			VertexPositionColorTexture& topVertex = renderData.vertices[0];
			topVertex.textureCoordinates.x = 0.5f;
			topVertex.textureCoordinates.y = 1.0f;

			leftPoint.x = lx;
			leftPoint.y = ly;
			VertexPositionColorTexture& leftVertex = renderData.vertices[1];
			leftVertex.textureCoordinates.x = 0.0f;
			leftVertex.textureCoordinates.y = 0.0f;

			rightPoint.x = rx;
			rightPoint.y = ry;
			VertexPositionColorTexture& rightVertex = renderData.vertices[2];
			rightVertex.textureCoordinates.x = 1.0f;
			rightVertex.textureCoordinates.y = 0.0f;

			const float32 my = std::max(ly, ry);

			transform.origin.x = (rx - lx) / 2.0f;
			transform.origin.y = my / 2.0f;

			transform.position.x = lx;
			transform.position.y = ty;
			
			RenderElementData& shapeRenderData = renderData.renderElements[0];
			shapeRenderData.first = 0;
			shapeRenderData.last = 2;
			shapeRenderData.vertexElements = 7;	
			shapeRenderData.offset = 2;

			RenderElementData& borderRenderData = renderData.renderElements[1];
			borderRenderData.first = 3;
			borderRenderData.last = 5;
			borderRenderData.vertexElements = 7;
			borderRenderData.offset = 2;

			recomputeBounds(*this);
			recomputeVertices(*this);
			updateRenderData(*this);
		}
		Triangle::Triangle(const math::Vec2f& top, const math::Vec2f& left, const math::Vec2f& right) 
			: Triangle(top.x, top.y, left.x, left.y, right.x, right.y) {
		}
		Triangle::Triangle(const float32 x, const float32 y, const float32 width, const float32 height) 
			: Triangle(x + width / 2.0f, y, x, y + height, x + width, y + height) {
		}
		Triangle::Triangle(const math::Vec2f& position, const math::Vec2f& size) 
			: Triangle(position.x - size.x / 2.0f, position.y, position.x, position.y + size.y, position.x + size.x, position.y + size.y) {
		}
		Triangle::Triangle(const float32 width, const float32 height) 
			: Triangle(width / 2.0f, 0.0f, 0.0f, height, width, height) {
		}
	}
}