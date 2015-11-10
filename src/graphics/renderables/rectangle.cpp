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

		Rectangle::Rectangle(const float32 x, const float32 y, const float32 w, const float32 h) : Renderable(1, 1, 1) {
			initialize(x, y, w, h);
		}
		Rectangle::Rectangle(const sani::math::Vec2f& position, const sani::math::Vec2f& size) : Renderable(1, 1, 1){
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

			transform.position.x = x; 
			transform.position.y = y;
			transform.origin.x = localBounds.w / 2.0f;
			transform.origin.y = localBounds.h / 2.0f;

			recomputeGeometryData(*this);
		}
	}
}