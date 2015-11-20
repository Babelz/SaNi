#include "sani/graphics/renderables/rectangle.hpp"
#include "sani/core/math/trigonometric.hpp"
#include "sani/graphics/render_helper.hpp"
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
			const sani::math::Vec3f& position = rectangle.transform.position;
			const sani::math::Vec3f& origin = rectangle.transform.origin;
			const sani::math::Vec3f& scale = rectangle.transform.scale;
			const sani::math::Rectf& localBounds = rectangle.localBounds;
			const float32 rotation = rectangle.transform.rotation;

			const float32 sin = sani::math::sin(rotation);
			const float32 cos = sani::math::cos(rotation);

			const float32 dx = -origin.x * scale.x;
			const float32 dy = -origin.y * scale.y;

			VertexPositionColorTexture* shapeVertices[] {
				&rectangle.renderData.vertices[0],
				&rectangle.renderData.vertices[1],
				&rectangle.renderData.vertices[2],
				&rectangle.renderData.vertices[3]
			};

			sani::math::Vec3f shapeGlobalPositions[] {
				position,
				position,
				position,
				position
			};

			sani::math::Vec3f shapeVertexPositions[] {
				sani::math::Vec3f(0.0f, 0.0f, 0.0f),
				sani::math::Vec3f(0.0f, localBounds.h, 0.0f) * scale,
				sani::math::Vec3f(localBounds.w, localBounds.h, 0.0f) * scale,
				sani::math::Vec3f(localBounds.w, 0.0f, 0.0f) * scale
			};

			applyRotationToRectangle(shapeGlobalPositions, shapeVertexPositions, dx, dy, sin, cos);

			for (uint32 i = 0; i < 4; i++) {
				shapeVertices[i]->vertexPositionColor.position = shapeGlobalPositions[i];
				shapeVertices[i]->vertexPositionColor.color = rectangle.fill;
			}

			if (rectangle.borderThickness > 0.0f) {	
				VertexPositionColorTexture* borderVertices[] {
					&rectangle.renderData.vertices[4],
					&rectangle.renderData.vertices[5],
					&rectangle.renderData.vertices[6],
					&rectangle.renderData.vertices[7]
				};

				const float32 borderThickness = rectangle.borderThickness;
				const float32 doubleBorderThickness = borderThickness * 2.0f;
				
				sani::math::Vec3f borderGlobalPositions[] {
					position,
					position,
					position,
					position
				};

				sani::math::Vec3f borderVertexPositions[] {
					sani::math::Vec3f(0.0f, -doubleBorderThickness, position.z),
					sani::math::Vec3f(-borderThickness * 2.0f, localBounds.h + doubleBorderThickness, position.z),
					sani::math::Vec3f(localBounds.w + doubleBorderThickness, localBounds.h + doubleBorderThickness, position.z),
					sani::math::Vec3f(localBounds.w + doubleBorderThickness, -doubleBorderThickness, position.z)
				};

				applyRotationToRectangle(borderGlobalPositions, borderVertexPositions, dx - rectangle.borderThickness, dy - rectangle.borderThickness, sin, cos);

				for (uint32 i = 0; i < 4; i++) {
					borderVertices[i]->vertexPositionColor.position = borderGlobalPositions[i];
					borderVertices[i]->vertexPositionColor.color = rectangle.borderFill;
				}
			}
		}
		void recomputeBounds(Rectangle& rectangle) {
			const sani::math::Vec3f& position = rectangle.transform.position;
			const sani::math::Vec3f& scale = rectangle.transform.scale;

			rectangle.globalBounds.x = position.x;
			rectangle.globalBounds.y = position.y;
			rectangle.globalBounds.w = rectangle.localBounds.w * scale.x;
			rectangle.globalBounds.w = rectangle.localBounds.h * scale.y;
		}

		void updateRenderData(Rectangle& rectangle) {
			setupShapeForRendering(&rectangle, rectangle.borderThickness);

			if (rectangle.texture != nullptr) {
			}
		}
	}
}