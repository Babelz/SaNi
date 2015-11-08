#include "sani/graphics/renderables/triangle.hpp"
#include "sani/core/math/trigonometric.hpp"
#include "sani/graphics/vertex_helper.hpp"
#include "sani/graphics/renderer.hpp"

namespace sani {

	namespace graphics {

		void recomputeGeometryData(Triangle& triangle) {
			// TODO: could optimize, compute geometry data
			//		 only if points or transform has changed?
			//
			// TODO: optimize.

			recomputeBounds(triangle);
			recomputeVertices(triangle);
		}
		void recomputeVertices(Triangle& triangle)  {
			const sani::math::Vec3f& position = triangle.transform.getPosition();
			const sani::math::Vec3f& origin = triangle.transform.getOrigin();
			const sani::math::Vec3f& scale = triangle.transform.getScale();
			const float32 rotation = triangle.transform.getRotation();

			const float32 sin = sani::math::sin(rotation);
			const float32 cos = sani::math::cos(rotation);

			const float32 dx = -origin.x * scale.x;
			const float32 dy = -origin.y * scale.y;

			sani::math::Vec3f shapeGlobalPositions[] = 
			{
				// Transformed results will be placed in this array.
				position,		// Top.
				position,		// Left.
				position		// Right.
			};

			sani::math::Vec3f shapeVertexPositions[]
			{
				triangle.topPoint * scale,
				triangle.leftPoint * scale,
				triangle.rightPoint * scale
			};

			applyRotationToTriangle(shapeGlobalPositions, shapeVertexPositions, dx, dy, sin, cos);

			triangle.topVertex.vertexPositionColor.position = shapeGlobalPositions[0];
			triangle.leftVertex.vertexPositionColor.position = shapeGlobalPositions[1];
			triangle.rightVertex.vertexPositionColor.position = shapeGlobalPositions[2];

			triangle.topVertex.vertexPositionColor.color = triangle.fill;
			triangle.leftVertex.vertexPositionColor.color = triangle.fill;
			triangle.rightVertex.vertexPositionColor.color = triangle.fill;

			// Compute border vertices if needed.
			if (triangle.borderThickness > 0.0f) {
				sani::math::Vec3f borderTopPoint = triangle.topPoint;
				borderTopPoint.x += triangle.borderThickness;
				borderTopPoint.y += triangle.borderThickness;

				sani::math::Vec3f borderLeftPoint = triangle.leftPoint;
				borderLeftPoint.x -= triangle.borderThickness * 4.0f;
				borderLeftPoint.y += triangle.borderThickness * 1.5f;

				sani::math::Vec3f borderRightPoint = triangle.rightPoint;
				borderRightPoint.x += triangle.borderThickness * 2.0f;
				borderRightPoint.y += triangle.borderThickness * 1.5f;
				
				sani::math::Vec3f borderGlobalPositions[] =
				{
					// Transformed results will be placed in this array.
					position,		// Top.
					position,		// Left.
					position		// Right.
				};

				sani::math::Vec3f borderVertexPositions[]
				{
					borderTopPoint * scale,
					borderLeftPoint * scale,
					borderRightPoint * scale
				};

				applyRotationToTriangle(borderGlobalPositions, borderVertexPositions, dx - triangle.borderThickness, dy - triangle.borderThickness, sin, cos);

				triangle.topBorderVertex.position = borderGlobalPositions[0];
				triangle.leftBorderVertex.position = borderGlobalPositions[1];
				triangle.rightBorderVertex.position = borderGlobalPositions[2];

				triangle.topBorderVertex.color = triangle.borderFill;
				triangle.leftBorderVertex.color = triangle.borderFill;
				triangle.rightBorderVertex.color = triangle.borderFill;
			}
		}
		void recomputeBounds(Triangle& triangle) {
			// Recompute local bounds.
			const float32 maxHeight = std::fmax(triangle.leftPoint.y, triangle.rightPoint.y);
			
			// Compute local bounds.
			math::Rectf localBounds;

			localBounds.x = 0.0f;
			localBounds.y = 0.0f;
			localBounds.w = triangle.rightPoint.x - triangle.leftPoint.x;
			localBounds.h = maxHeight - triangle.topPoint.y;

			// Recompute global bounds.
			const sani::math::Vec3f& position = triangle.transform.getPosition();
			const sani::math::Vec3f& scale = triangle.transform.getScale();
			math::Rectf globalBounds;

			globalBounds.x = position.x;
			globalBounds.y = position.y;
			globalBounds.w = localBounds.w * scale.x;
			globalBounds.h = localBounds.h * scale.y;
			
			// Store new bound data.
			triangle.globalBounds = globalBounds;
			triangle.localBounds = localBounds;
		}

		bool canRender(const Triangle& triangle, const Renderer& renderer) {
			const RenderState renderState	 =	triangle.texture == nullptr ? RenderState::Polygons : RenderState::TexturedPolygons;
			const uint32 vertexElementsCount =	getVertexElementsCount(triangle);

			return renderer.getVertexMode() == VertexMode::NoIndexing && renderer.getVertexElementsCount() == vertexElementsCount &&
				   renderer.getRenderState() == renderState;
		}
		void render(Triangle& triangle, Renderer& renderer) {
		
			// TODO: add texture checking.
			if (triangle.borderThickness > 0.0f) {
				VertexPositionColor borderVertexData[] =
				{
					triangle.topBorderVertex,
					triangle.leftBorderVertex,
					triangle.rightBorderVertex
				};

				renderer.renderPolygons(reinterpret_cast<float32*>(borderVertexData), 21);
			}

			// TODO: add texture checking.
			VertexPositionColor shapeVertexData[] =
			{
				triangle.topVertex.vertexPositionColor,
				triangle.leftVertex.vertexPositionColor,
				triangle.rightVertex.vertexPositionColor
			};

			renderer.renderPolygons(reinterpret_cast<float32*>(shapeVertexData), 21);
		}

		const uint32 getVertexElementsCount(const Triangle& triangle) {
			return triangle.texture == nullptr ? 7 : 9;
		}
	}
}