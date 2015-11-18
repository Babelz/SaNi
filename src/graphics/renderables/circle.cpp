#include "sani/graphics/renderables/circle.hpp"

namespace sani {

	namespace graphics {

		Circle::Circle(const float32 x, const float32 y, const float32 radius, const uint32 vertices) : Renderable((vertices * 2) + 2, 2),
																									    vertices(vertices) {
			this->radius = radius;

			borderThickness = 0.0f;
			borderFill = color::green;

			fill = color::red;

			// TODO: texture coordinates.

			transform.position.x = x;
			transform.position.y = y;
			transform.origin.x = radius;
			transform.origin.y = radius;

			localBounds.w = radius * 2.0f;
			localBounds.h = radius * 2.0f;

			recomputeGeometryData(*this);
			updateRenderData(*this);
			
			RenderElementData& shapeRenderData = renderData.renderElements[0];
			shapeRenderData.first = 0;
			shapeRenderData.last = vertices + 1;	// +1 caused by center vertex.
			shapeRenderData.vertexElements = 7;		// TODO: no texturing.
			shapeRenderData.offset = 2;
			shapeRenderData.renderMode = RenderMode::TriangleFan;

			RenderElementData& borderRenderData = renderData.renderElements[1];
			borderRenderData.first = vertices + 2;		// End of shape vertices + shape center + border center.
			borderRenderData.last = vertices * 2 + 1;	// Shape + border center offset.
			borderRenderData.vertexElements = 7;
			borderRenderData.offset = 2;
			borderRenderData.renderMode = RenderMode::TriangleFan;

			updateGroupIdentifier(*this);
		}
		Circle::Circle(const sani::math::Vec2f& position, const float32 radius, const uint32 vertices) : Circle(position.x, position.y, radius, vertices) {
		}
		Circle::Circle(const float32 radius, const uint32 vertices) : Circle(0.0f, 0.0f, radius, vertices) {
		}
		Circle::Circle(const float32 radius) : Circle(0.0f, 0.0f, radius, VERTICES_SMOOTH_CIRCLE) {
		}
		Circle::Circle() : Circle(1.0f, VERTICES_ROUGH_CIRCLE) {
		}
	}
}