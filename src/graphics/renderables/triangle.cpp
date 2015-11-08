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

		Triangle::Triangle(const float32 tx, const float32 ty, const float32 lx, const float32 ly, const float32 rx, const float32 ry) {
			initialize(tx, ty, lx, ly, rx, ry);
		}
		Triangle::Triangle(const sani::math::Vec2f& top, const sani::math::Vec2f& left, const sani::math::Vec2f& right) {
			initialize(top.x, top.y, left.x, left.y, right.x, right.y);
		}
		Triangle::Triangle(const float32 x, const float32 y, const float32 width, const float32 height) {
			initialize(x + width / 2.0f, y, x, y + height, x + width, y + height);
		}
		Triangle::Triangle(const sani::math::Vec2f& position, const sani::math::Vec2f& size) {
			initialize(position.x - size.x / 2.0f, position.y, position.x, position.y + size.y, position.x + size.x, position.y + size.y);
		}
		Triangle::Triangle(const float32 width, const float32 height) {
			initialize(width / 2.0f, 0.0f, 0.0f, height, width, height);
		}

		void Triangle::initialize(const float32 tx, const float32 ty, const float32 lx, const float32 ly, const float32 rx, const float32 ry) {
			/*
				Store points and set texture coordinates.
			*/

			fill = color::red;
			borderFill = color::green;

			// Default no border.
			borderThickness = 0.0f;

			topPoint.x = tx;
			topPoint.y = ty;
			topVertex.textureCoordinates.x = 0.5f;
			topVertex.textureCoordinates.y = 1.0f;

			leftPoint.x = lx;
			leftPoint.y = ly;
			leftVertex.textureCoordinates.x = 0.0f;
			leftVertex.textureCoordinates.y = 1.0f;

			rightPoint.x = rx;
			rightPoint.y = ry;
			rightVertex.textureCoordinates.x = 1.0f;
			rightVertex.textureCoordinates.y = 1.0f;

			transform.setPosition(rx, ty);
			transform.setOrigin(localBounds.w / 2.0f, localBounds.h / 2.0f);
			
			recomputeGeometryData(*this);
		}
	}
}