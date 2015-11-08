#include "sani/graphics/renderables/rectangle.hpp"
#include "sani/core/math/trigonometric.hpp"
#include "sani/graphics/vertex_helper.hpp"
#include "sani/graphics/renderer.hpp"

namespace sani {

	namespace graphics {

		void recomputeGeometryData(Rectangle& rectangle) {
			// TODO: could optimize, compute geometry data
			//		 only if points or transform has changed?
			//
			// TODO: optimize.

			recomputeBounds(rectangle);
			recomputeVertices(rectangle);
		}
		void recomputeVertices(Rectangle& rectangle) {
			const sani::math::Vec3f& position = rectangle.transform.getPosition();
			const sani::math::Vec3f& origin = rectangle.transform.getOrigin();
			const sani::math::Vec3f& scale = rectangle.transform.getScale();
			const sani::math::Rectf& localBounds = rectangle.localBounds;
			const float32 rotation = rectangle.transform.getRotation();

			const float32 sin = sani::math::sin(rotation);
			const float32 cos = sani::math::cos(rotation);

			const float32 dx = -origin.x * scale.x;
			const float32 dy = -origin.y * scale.y;

			sani::math::Vec3f shapeGlobalPositions[] = 
			{
				position,
				position,
				position,
				position
			};

			sani::math::Vec3f shapeVertexPositions[] =
			{
				sani::math::Vec3f(0.0f, 0.0f, 0.0f),
				sani::math::Vec3f(0.0f, localBounds.h, 0.0f) * scale,
				sani::math::Vec3f(localBounds.w, localBounds.h, 0.0f) * scale,
				sani::math::Vec3f(localBounds.w, 0.0f, 0.0f) * scale
			};

			applyRotationToRectangle(shapeGlobalPositions, shapeVertexPositions, dx, dy, sin, cos);

			rectangle.topLeftVertex.vertexPositionColor.position = shapeGlobalPositions[0];
			rectangle.bottomLeftVertex.vertexPositionColor.position = shapeGlobalPositions[1];
			rectangle.bottomRightVertex.vertexPositionColor.position = shapeGlobalPositions[2];
			rectangle.topRightVertex.vertexPositionColor.position = shapeGlobalPositions[3];

			rectangle.topLeftVertex.vertexPositionColor.color = rectangle.fill;
			rectangle.bottomLeftVertex.vertexPositionColor.color = rectangle.fill;
			rectangle.bottomRightVertex.vertexPositionColor.color = rectangle.fill;
			rectangle.topRightVertex.vertexPositionColor.color = rectangle.fill;

			if (rectangle.borderThickness > 0.0f) {				
				sani::math::Vec3f borderTopLeftPoint;
				borderTopLeftPoint.x = 0.0f;
				borderTopLeftPoint.y = -rectangle.borderThickness * 2.0f;
				
				sani::math::Vec3f borderBottomLeftPoint;
				borderBottomLeftPoint.x = -rectangle.borderThickness * 2.0f;
				borderBottomLeftPoint.y = localBounds.h + rectangle.borderThickness * 2.0f;
				
				sani::math::Vec3f borderBottomRightPoint;
				borderBottomRightPoint.x = localBounds.w + rectangle.borderThickness * 2.0f;
				borderBottomRightPoint.y = localBounds.h + rectangle.borderThickness * 2.0f;
				
				sani::math::Vec3f borderTopRightPoint;
				borderTopRightPoint.x = localBounds.w + rectangle.borderThickness * 2.0f;
				borderTopRightPoint.y = -rectangle.borderThickness * 2.0f;
				
				sani::math::Vec3f borderGlobalPositions[] =
				{
					position,
					position,
					position,
					position
				};

				sani::math::Vec3f borderVertexPositions[] = 
				{
					borderTopLeftPoint,
					borderBottomLeftPoint,
					borderBottomRightPoint,
					borderTopRightPoint
				};

				applyRotationToRectangle(borderGlobalPositions, borderVertexPositions, dx - rectangle.borderThickness, dy - rectangle.borderThickness, sin, cos);

				rectangle.topLeftBorderVertex.position = borderGlobalPositions[0];
				rectangle.bottomLeftBorderVertex.position = borderGlobalPositions[1];
				rectangle.bottomRightBorderVertex.position = borderGlobalPositions[2];
				rectangle.topRightBorderVertex.position = borderGlobalPositions[3];

				rectangle.topLeftBorderVertex.color = rectangle.borderFill;
				rectangle.bottomLeftBorderVertex.color = rectangle.borderFill;
				rectangle.bottomRightBorderVertex.color = rectangle.borderFill;
				rectangle.topRightBorderVertex.color = rectangle.borderFill;
			}
		}
		void recomputeBounds(Rectangle& rectangle) {
			const sani::math::Vec3f& position = rectangle.transform.getPosition();
			const sani::math::Rectf localBounds = rectangle.localBounds;
			sani::math::Rectf globalBounds;

			globalBounds.x = position.x;
			globalBounds.y = position.y;
			globalBounds.w = localBounds.w;
			globalBounds.w = localBounds.h;
		}

		bool canRender(const Rectangle& rectangle, const Renderer& renderer) {
			const RenderState renderState	 = rectangle.texture == nullptr ? RenderState::Polygons : RenderState::TexturedPolygons;
			const uint32 vertexElementsCount = getVertexElementsCount(rectangle);
			
			return renderer.getVertexMode() == VertexMode::Indexed && renderer.getVertexElementsCount() == vertexElementsCount &&
				   renderer.getRenderState() == renderState;
		}
		void render(Rectangle& rectangle, Renderer& renderer) {
			const uint32 indices[] =
			{
				0, 1, 2,
				0, 3, 2
			};

			if (rectangle.borderThickness > 0.0f) {
				VertexPositionColor borderVertexData[] =
				{
					rectangle.topLeftBorderVertex,
					rectangle.bottomLeftBorderVertex,
					rectangle.bottomRightBorderVertex,
					rectangle.topRightBorderVertex
				};
			
				renderer.renderIndexedPolygons(reinterpret_cast<float32*>(borderVertexData), indices, 28, 6, 1);
			}
			
			// TODO: add texture checking.
			VertexPositionColor shapeVertexData[]= 
			{
				rectangle.topLeftVertex.vertexPositionColor,
				rectangle.bottomLeftVertex.vertexPositionColor,
				rectangle.bottomRightVertex.vertexPositionColor,
				rectangle.topRightVertex.vertexPositionColor
			};

			renderer.renderIndexedPolygons(reinterpret_cast<float32*>(shapeVertexData), indices, 28, 6, 1);
		}

		const uint32 getVertexElementsCount(const Rectangle& rectangle) {
			return rectangle.texture == nullptr ? 7 : 9;
		}
	}
}