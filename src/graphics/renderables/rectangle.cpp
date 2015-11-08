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

		Rectangle::Rectangle(const float32 x, const float32 y, const float32 w, const float32 h) {
			initialize(x, y, w, h);
		}
		Rectangle::Rectangle(const sani::math::Vec2f& position, const sani::math::Vec2f& size) {
			initialize(position.x, position.y, size.x, size.y);
		}

		void Rectangle::initialize(const float32 x, const float32 y, const float32 w, const float32 h) {
			fill = color::red;
			borderFill = color::green;

			borderThickness = 0.0f;

			localBounds.w = w;
			localBounds.h = h;
			
			topLeftVertex.textureCoordinates.x = 0.0f;
			topLeftVertex.textureCoordinates.y = 0.0f;

			topRightVertex.textureCoordinates.x = 1.0f;
			topRightVertex.textureCoordinates.y = 0.0f;

			bottomLeftVertex.textureCoordinates.x = 0.0f;
			bottomLeftVertex.textureCoordinates.y = 1.0f;

			bottomRightVertex.textureCoordinates.x = 1.0f;
			bottomRightVertex.textureCoordinates.y = 1.0f;

			transform.setPosition(x, y);
			transform.setOrigin(localBounds.w / 2.0f, localBounds.h / 2.0f);

			recomputeGeometryData(*this);
		}
	}
}