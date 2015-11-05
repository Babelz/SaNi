#include "sani/graphics/renderables/triangle.hpp"
#include "sani/graphics/renderer.hpp"
#include "sani/core/math/vector.hpp"

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
		Triangle::Triangle(const float32 width, const float32 height) {
			initialize(width / 2.0f, 0.0f, 0.0f, height, width, height);
		}

		void Triangle::initialize(const float32 tx, const float32 ty, const float32 lx, const float32 ly, const float32 rx, const float32 ry) {
			/*
				Store points and set texture coordinates.
			*/

			topPoint.x = tx;
			topPoint.y = ty;
			topVertex.vertexPositionColor.position = topPoint;
			topVertex.textureCoordinates.x = 0.5f;
			topVertex.textureCoordinates.y = 1.0f;

			leftPoint.x = lx;
			leftPoint.y = ly;
			leftVertex.vertexPositionColor.position = leftPoint;
			leftVertex.textureCoordinates.x = 0.0f;
			leftVertex.textureCoordinates.y = 1.0f;

			rightPoint.x = rx;
			rightPoint.y = ry;
			rightVertex.vertexPositionColor.position = rightPoint;
			rightVertex.textureCoordinates.x = 1.0f;
			rightVertex.textureCoordinates.y = 1.0f;

			setPosition(rx, ty);

			// TODO: set origin

			recomputeVertices();
		}
		void Triangle::recomputeVertices()  {
			if (hasChanged()) {
				const sani::math::Vec3f position = getPosition();
				
				topVertex.vertexPositionColor.position = topPoint + position;
				leftVertex.vertexPositionColor.position = leftPoint + position;
				rightVertex.vertexPositionColor.position = rightPoint + position;

				topVertex.vertexPositionColor.color = getFill();
				leftVertex.vertexPositionColor.color = getFill();
				rightVertex.vertexPositionColor.color = getFill();

				clearChanges();
			}
		}

		const math::Rectf Triangle::getLocalBounds() const {
			return math::Rectf();
		}
		const math::Rectf Triangle::getGlobalBounds() const {
			return math::Rectf();
		}

		const sani::math::Vec3f& Triangle::getTop() const {
			return topVertex.vertexPositionColor.position;
		}
		const sani::math::Vec3f& Triangle::getLeft() const {
			return topVertex.vertexPositionColor.position;
		}
		const sani::math::Vec3f& Triangle::getRight() const {
			return topVertex.vertexPositionColor.position;
		}

		void Triangle::setTop(const Vec3f& top) {
		}
		void Triangle::setRight(const Vec3f& right) {
		}
		void Triangle::setLeft(const Vec3f& top) {
		}

		void Triangle::setTop(const float32 x, const float32 y) {
		}
		void Triangle::setRight(const float32 x, const float32 y) {
		}
		void Triangle::setLeft(const float32 x, const float32 y) {
		}

		void Triangle::render(Renderer* const renderer) {
			if (hasChanged()) recomputeVertices();

			VertexPositionColor vertices[] = 
			{
				topVertex.vertexPositionColor,
				leftVertex.vertexPositionColor,
				rightVertex.vertexPositionColor
			};

			renderer->renderPolygon(reinterpret_cast<float32*>(vertices), sizeof(vertices));
		}
	}
}