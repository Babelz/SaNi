#include "sani/graphics/renderables/triangle.hpp"
#include "sani/core/math/trigonometric.hpp"
#include "sani/graphics/vertex_helper.hpp"
#include "sani/graphics/renderer.hpp"
#include "sani/core/math/vector.hpp"


namespace sani {

	namespace graphics {

		bool canRender(const Triangle& triangle, const Renderer& renderer) {
			// TODO: add texture checking once textures can be loaded.
			const uint32 vertexElementsCount = 7;

			// TODO: add texture checking once textures can be loaded.
			return renderer.getVertexMode() == VertexMode::NoIndexing && renderer.getVertexElementsCount() == vertexElementsCount &&
				   renderer.getRenderState() == RenderState::Polygons;
		}
		void render(const Triangle& triangle, Renderer& renderer) {
			// No need for state checks, we assume that
			// the LLR is in a valid state for this
			// element to be rendered.

			VertexPositionColor vertices[] =
			{
				triangle.topVertex.vertexPositionColor,
				triangle.leftVertex.vertexPositionColor,
				triangle.rightVertex.vertexPositionColor
			};

			renderer.renderPolygon(reinterpret_cast<float32*>(vertices), sizeof(vertices));
		}
		
		void recomputeVertices(Triangle& triangle) {
			if (triangle.transform.hasChanged()) {
				// Just do the bound recomputation here.
				// Done here + if the user changes any of 
				// the points location.
				recomputeBounds(triangle);

				const sani::math::Vec3f& position = triangle.transform.getPosition();
				const sani::math::Vec3f& origin = triangle.transform.getOrigin();
				const sani::math::Vec3f& scale = triangle.transform.getScale();
				const float32 rotation = triangle.transform.getRotation();

				const float32 sin = sani::math::sin(rotation);
				const float32 cos = sani::math::cos(rotation);

				const float32 dx = -origin.x * scale.x;
				const float32 dy = -origin.y * scale.y;

				sani::math::Vec3f topTransformPoint = position;
				applyRotationToTopLeftVertex(topTransformPoint, triangle.topPoint * scale, dx, dy, sin, cos);

				sani::math::Vec3f leftTransformPoint = position;
				applyRotationToBottomLeftVertex(leftTransformPoint, triangle.leftPoint * scale, dx, dy, sin, cos);

				sani::math::Vec3f rightTransformPoint = position;
				applyRotationToBottomRightVertex(rightTransformPoint, triangle.rightPoint * scale, dx, dy, sin, cos);

				triangle.topVertex.vertexPositionColor.position = topTransformPoint;
				triangle.leftVertex.vertexPositionColor.position = leftTransformPoint;
				triangle.rightVertex.vertexPositionColor.position = rightTransformPoint;

				triangle.topVertex.vertexPositionColor.color = triangle.fill;
				triangle.leftVertex.vertexPositionColor.color = triangle.fill;
				triangle.rightVertex.vertexPositionColor.color = triangle.fill;

				triangle.transform.clearChanges();
			}
		}
		void recomputeBounds(Triangle& triangle) {
			const float32 maxHeight = std::fmax(triangle.leftPoint.y, triangle.rightPoint.y);
			math::Rectf globalBounds;

			// Compute local bounds.
			math::Rectf localBounds;

			localBounds.x = 0.0f;
			localBounds.y = 0.0f;
			localBounds.w = triangle.rightPoint.x - triangle.leftPoint.x;
			localBounds.h = maxHeight - triangle.topPoint.y;

			// Recompute global bounds.
			const sani::math::Vec3f& position = triangle.transform.getPosition();
			const sani::math::Vec3f& scale = triangle.transform.getScale();

			globalBounds.x = position.x;
			globalBounds.y = position.y;
			globalBounds.w = (triangle.rightPoint.x - triangle.leftPoint.x) * scale.x;
			globalBounds.h = (maxHeight - triangle.topPoint.y) * scale.y;

			// Store new values.
			triangle.localBounds = localBounds;
			triangle.globalBounds = globalBounds;
		}
	}
}