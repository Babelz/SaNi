#include "sani/graphics/renderables/triangle.hpp"
#include "sani/core/math/trigonometric.hpp"
#include "sani/graphics/render_helper.hpp"
#include "sani/graphics/vertex_helper.hpp"
#include "sani/graphics/renderer.hpp"
#include "sani/platform.hpp"
#include <algorithm>

namespace sani {

	namespace graphics {

		void recomputeVertices(Triangle& triangle)  {
			const math::Vec3f& position = triangle.transform.position;
			const math::Vec3f& origin = triangle.transform.origin;
			const math::Vec3f& scale = triangle.transform.scale;
			const float32 rotation = triangle.transform.rotation;

			const float32 sin = math::sin(rotation);
			const float32 cos = math::cos(rotation);

			const float32 dx = -origin.x * scale.x;
			const float32 dy = -origin.y * scale.y;

			math::Vec3f shapeGlobalPositions[]  {
				// Transformed results will be placed in this array.
				position,		// Top.
				position,		// Left.
				position		// Right.
			};

			math::Vec3f shapeVertexPositions[] {
				triangle.topPoint * scale,
				triangle.leftPoint * scale,
				triangle.rightPoint * scale
			};

			VertexPositionColorTexture* shapeVertices[] {
				&triangle.renderData.vertices[0],	// Top.
				&triangle.renderData.vertices[1],	// Left.
				&triangle.renderData.vertices[2]	// Right.
			};

			applyRotationToTriangle(shapeGlobalPositions, shapeVertexPositions, dx, dy, sin, cos);

			for (uint32 i = 0; i < 3; i++) {
				shapeVertices[i]->vertexPositionColor.position = shapeGlobalPositions[i];
				shapeVertices[i]->vertexPositionColor.color = triangle.fill;
			}

			// Compute border vertices if needed.
			if (triangle.borderThickness > 0.0f) {
				math::Vec3f borderTopPoint = triangle.topPoint * scale;
				borderTopPoint.x += triangle.borderThickness;
				borderTopPoint.y += triangle.borderThickness;

				math::Vec3f borderLeftPoint = triangle.leftPoint * scale;
				borderLeftPoint.x -= triangle.borderThickness * 4.0f;
				borderLeftPoint.y += triangle.borderThickness * 1.5f;

				math::Vec3f borderRightPoint = triangle.rightPoint * scale;
				borderRightPoint.x += triangle.borderThickness * 2.0f;
				borderRightPoint.y += triangle.borderThickness * 1.5f;
				
				math::Vec3f borderGlobalPositions[] {
					// Transformed results will be placed in this array.
					position,		// Top.
					position,		// Left.
					position		// Right.
				};

				math::Vec3f borderVertexPositions[]
				{
					borderTopPoint,
					borderLeftPoint,
					borderRightPoint
				};

				VertexPositionColorTexture* borderVertices[] {
					&triangle.renderData.vertices[3],	// Top.
					&triangle.renderData.vertices[4],	// Left.
					&triangle.renderData.vertices[5]	// Right.
				};

				applyRotationToTriangle(borderGlobalPositions, borderVertexPositions, dx - triangle.borderThickness, dy - triangle.borderThickness, sin, cos);

				for (uint32 i = 0; i < 3; i++) {
					borderVertices[i]->vertexPositionColor.position = borderGlobalPositions[i];
					borderVertices[i]->vertexPositionColor.color = triangle.borderFill;
				}
			} 
		}
		void recomputeBounds(Triangle& triangle) {
			// Recompute local bounds.
			const float32 maxHeight = std::max(triangle.leftPoint.y, triangle.rightPoint.y);
			
			// Compute local bounds.
			triangle.localBounds.x = 0.0f;
			triangle.localBounds.y = 0.0f;
			triangle.localBounds.w = triangle.rightPoint.x - triangle.leftPoint.x;
			triangle.localBounds.h = maxHeight - triangle.topPoint.y;

			// Recompute global bounds.
			const math::Vec3f& position = triangle.transform.position;
			const math::Vec3f& scale = triangle.transform.scale;
			
			triangle.globalBounds.x = position.x;
			triangle.globalBounds.y = position.y;
			triangle.globalBounds.w = triangle.localBounds.w * scale.x;
			triangle.globalBounds.h = triangle.localBounds.h * scale.y;
		}
	
		void updateRenderData(Triangle& triangle) {
			setupShapeForRendering(&triangle, triangle.borderThickness);
			
			if (triangle.texture == nullptr) {
				useSolidFill(&triangle);
			} else {
				if (!triangle.textureSource.isEmpty()) {
					VertexPositionColorTexture* vertices[] {
						&triangle.renderData.vertices[0],
						&triangle.renderData.vertices[1],
						&triangle.renderData.vertices[2]
					};

					computeTriangleTextureCoordinates(vertices, 
													  triangle.textureSource, 
													  static_cast<float32>(triangle.texture->getWidth()),
													  static_cast<float32>(triangle.texture->getHeight()));
				}

				useTexturing(&triangle);
			}

			updateGroupIdentifier(triangle);
		}
	}
}