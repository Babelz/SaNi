#include "sani/graphics/renderables/triangle.hpp"
#include "sani/core/math/trigonometric.hpp"
#include "sani/graphics/vertex_helper.hpp"
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

			recomputeBounds();
			recomputeVertices();

			clearChanges();
		}
	
		void Triangle::recomputeBounds() {
			// Recompute local bounds.
			const float32 maxHeight = std::fmax(leftPoint.y, rightPoint.y);

			localBounds.x = 0.0f;
			localBounds.y = 0.0f;
			localBounds.w = rightPoint.x - leftPoint.x;
			localBounds.h = maxHeight - topPoint.y;

			// Recompute global bounds.
			const sani::math::Vec3f& position = getPosition();
			const sani::math::Vec3f& scale = getScale();

			globalBounds.x = position.x;
			globalBounds.y = position.y;
			globalBounds.w = (rightPoint.x - leftPoint.x) * scale.x;
			globalBounds.h = (maxHeight - topPoint.y) * scale.y;
		}

		const math::Rectf& Triangle::getLocalBounds() const {
			return localBounds;
		}
		const math::Rectf& Triangle::getGlobalBounds() const {
			return globalBounds;
		}

		sani::math::Vec2f Triangle::getTop() const {
			return math::Vec2f(topPoint.x, topPoint.y);
		}
		sani::math::Vec2f Triangle::getLeft() const {
			return math::Vec2f(leftPoint.x, leftPoint.y);
		}
		sani::math::Vec2f Triangle::getRight() const {
			return math::Vec2f(rightPoint.x, rightPoint.y);
		}

		void Triangle::setTop(const Vec2f& top) {
			topPoint.x = top.x;
			topPoint.y = top.y;
			
			recomputeBounds();
			recomputeVertices();

			clearChanges();
		}
		void Triangle::setRight(const Vec2f& right) {
			rightPoint.x = right.x;
			rightPoint.y = right.y;

			recomputeBounds();
			recomputeVertices();

			clearChanges();
		}
		void Triangle::setLeft(const Vec2f& left) {
			leftPoint.x = left.x;
			leftPoint.y = left.y;

			recomputeBounds();
			recomputeVertices();

			clearChanges();
		}

		void Triangle::setTop(const float32 x, const float32 y) {
			const sani::math::Vec2f top(x, y);

			setTop(top);
		}
		void Triangle::setRight(const float32 x, const float32 y) {
			const sani::math::Vec2f right(x, y);

			setRight(right);
		}
		void Triangle::setLeft(const float32 x, const float32 y) {
			const sani::math::Vec2f left(x, y);

			setLeft(left);
		}

		void Triangle::render(Renderer* const renderer) {
			// No need for state checks, we assume that
			// the LLR is in a valid state for this
			// element to be rendered.

			VertexPositionColor vertices[] = 
			{
				topVertex.vertexPositionColor,
				leftVertex.vertexPositionColor,
				rightVertex.vertexPositionColor
			};

			renderer->renderPolygon(reinterpret_cast<float32*>(vertices), sizeof(vertices));
		}

		void Triangle::recomputeVertices()  {
			if (hasChanged()) {
				// Just do the bound recomputation here.
				// Done here + if the user changes any of 
				// the points location.
				recomputeBounds();

				const sani::math::Vec3f& position = getPosition();
				const sani::math::Vec3f& origin = getOrigin();
				const sani::math::Vec3f& scale = getScale();
				const float32 rotation = getRotation();

				const float32 sin = sani::math::sin(rotation);
				const float32 cos = sani::math::cos(rotation);

				const float32 dx = -origin.x * scale.x;
				const float32 dy = -origin.y * scale.y;

				sani::math::Vec3f topTransformPoint = position;
				applyRotationToTopLeftVertex(topTransformPoint, topPoint * scale, dx, dy, sin, cos);

				sani::math::Vec3f leftTransformPoint = position;
				applyRotationToBottomLeftVertex(leftTransformPoint, leftPoint * scale, dx, dy, sin, cos);

				sani::math::Vec3f rightTransformPoint = position;
				applyRotationToBottomRightVertex(rightTransformPoint, rightPoint * scale, dx, dy, sin, cos);

				topVertex.vertexPositionColor.position = topTransformPoint;
				leftVertex.vertexPositionColor.position = leftTransformPoint;
				rightVertex.vertexPositionColor.position = rightTransformPoint;

				topVertex.vertexPositionColor.color = getFill();
				leftVertex.vertexPositionColor.color = getFill();
				rightVertex.vertexPositionColor.color = getFill();

				clearChanges();
			}
		}

		bool Triangle::canRender(const Renderer* const renderer) const {
			// TODO: do texturing checking.
			const uint32 vertexElementsCount = 7;

			// TODO: to texturing checking.
			return renderer->getVertexMode() == VertexMode::NoIndexing && renderer->getVertexElementsCount() == vertexElementsCount &&
				   renderer->getRenderState() == RenderState::Polygons;
		}
	}
}