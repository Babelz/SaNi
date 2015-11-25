#include "sani/graphics/renderables/rectangle.hpp"
#include "sani/core/math/trigonometric.hpp"
#include "sani/graphics/render_helper.hpp"
#include "sani/graphics/vertex_helper.hpp"

namespace sani {

	namespace graphics {

		void recomputeVertices(Rectangle& rectangle) {
			const math::Vec3f& position = rectangle.transform.position;
			const math::Vec3f& origin = rectangle.transform.origin;
			const math::Vec3f& scale = rectangle.transform.scale;
			const math::Rectf& localBounds = rectangle.localBounds;
			const float32 rotation = rectangle.transform.rotation;

			const float32 sin = math::sin(rotation);
			const float32 cos = math::cos(rotation);

			const float32 dx = -origin.x * scale.x;
			const float32 dy = -origin.y * scale.y;

			VertexPositionColorTexture* shapeVertices[] {
				&rectangle.renderData.vertices[0],
				&rectangle.renderData.vertices[1],
				&rectangle.renderData.vertices[2],
				&rectangle.renderData.vertices[3]
			};

			math::Vec3f shapeGlobalPositions[] {
				position,
				position,
				position,
				position
			};

			math::Vec3f shapeVertexPositions[] {
				math::Vec3f(0.0f, 0.0f, 0.0f),								// Top left
				math::Vec3f(localBounds.w, 0.0f, 0.0f) * scale,				// Top right
				math::Vec3f(0.0f, localBounds.h, 0.0f) * scale,				// Bottom left
				math::Vec3f(localBounds.w, localBounds.h, 0.0f) * scale		// Bottom right
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
				
				math::Vec3f borderGlobalPositions[] {
					position,
					position,
					position,
					position
				};

				math::Vec3f borderVertexPositions[] {
					math::Vec3f(0.0f, 0.0f, 0.0f),																				// Top left
					math::Vec3f(localBounds.w + doubleBorderThickness, 0.0f, 0.0f) * scale,										// Top right
					math::Vec3f(-doubleBorderThickness, localBounds.h + doubleBorderThickness, 0.0f) * scale,						// Bottom left
					math::Vec3f(localBounds.w + doubleBorderThickness, localBounds.h + doubleBorderThickness, 0.0f) * scale		// Bottom right
				};

				applyRotationToRectangle(borderGlobalPositions, borderVertexPositions, dx - rectangle.borderThickness, dy - rectangle.borderThickness, sin, cos);

				for (uint32 i = 0; i < 4; i++) {
					borderVertices[i]->vertexPositionColor.position = borderGlobalPositions[i];
					borderVertices[i]->vertexPositionColor.color = rectangle.borderFill;
				}
			}
		}
		void recomputeBounds(Rectangle& rectangle) {
			const math::Vec3f& position = rectangle.transform.position;
			const math::Vec3f& scale = rectangle.transform.scale;

			rectangle.globalBounds.x = position.x;
			rectangle.globalBounds.y = position.y;
			rectangle.globalBounds.w = rectangle.localBounds.w * scale.x;
			rectangle.globalBounds.w = rectangle.localBounds.h * scale.y;
		}

		void updateRenderData(Rectangle& rectangle) {
			setupShapeForRendering(&rectangle, rectangle.borderThickness);

			if (rectangle.texture == nullptr) {
				// No texture, just use solid fill.
				useSolidFill(&rectangle);
			} else {
				// Use texturing, recompute texture coordinates if needed.
				if (!rectangle.textureSource.isEmpty()) {
					math::Vec2f* textureCoordinates[] {
						&rectangle.renderData.vertices[0].textureCoordinates,
						&rectangle.renderData.vertices[1].textureCoordinates,
						&rectangle.renderData.vertices[2].textureCoordinates,
						&rectangle.renderData.vertices[3].textureCoordinates
					};

					computeRectangleTextureCoordinates(textureCoordinates, 
													   &rectangle.textureSource, 
													   static_cast<float32>(rectangle.texture->getWidth()), 
													   static_cast<float32>(rectangle.texture->getHeight()));
				}

				useTexturing(&rectangle);
			}

			updateGroupIdentifier(rectangle);
		}
	}
}