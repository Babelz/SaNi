#include "sani/graphics/renderables/circle.hpp"

namespace sani {

	namespace graphics {

		Circle::Circle(const float32 x, const float32 y, const float32 radius, const uint32 vertices) {
			initialize(x, y, radius, vertices);
		}
		Circle::Circle(const sani::math::Vec2f& position, const float32 radius, const uint32 vertices) {
			initialize(position.x, position.y, radius, vertices);
		}
		Circle::Circle(const float32 radius, const uint32 vertices) {
			initialize(0.0f, 0.0f, radius, vertices);
		}
		Circle::Circle(const float32 radius) {
			initialize(0.0f, 0.0f, radius, VERTICES_SMOOTH_CIRCLE);
		}

		void Circle::initialize(const float32 x, const float32 y, const float32 radius, const uint32 vertices) {
			this->radius = radius;
			
			shapeVertices.resize(vertices);
			borderVertices.resize(vertices);

			borderThickness = 0.0f;
			borderFill = color::green;
			
			fill = color::red;

			// TODO: texture coordinates.

			transform.setPosition(x, y);
			transform.setOrigin(radius, radius);

			localBounds.w = radius * 2.0f;
			localBounds.h = radius * 2.0f;

			recomputeGeometryData(*this);
		}
	}
}