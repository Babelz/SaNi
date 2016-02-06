#include "sani/graphics/renderables/sprite.hpp"
#include "sani/core/math/trigonometric.hpp"
#include "sani/graphics/vertex_helper.hpp"

namespace sani {

	namespace graphics {

		void recomputeVertices(Sprite& sprite) {
			const math::Vec3f& position = sprite.transform.position;
			const math::Vec3f& origin = sprite.transform.origin;
			const math::Vec3f& scale = sprite.transform.scale;
			const math::Rect32f& localBounds = sprite.localBounds;
			const float32 rotation = sprite.transform.rotation;

			const float32 sin = math::sin(rotation);
			const float32 cos = math::cos(rotation);

			const float32 dx = -origin.x * scale.x;
			const float32 dy = -origin.y * scale.y;

			VertexPositionColorTexture* shapeVertices[] {
				&sprite.renderData.vertices[0],
				&sprite.renderData.vertices[1],
				&sprite.renderData.vertices[2],
				&sprite.renderData.vertices[3]
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
				shapeVertices[i]->vertexPositionColor.color = sprite.color;
			}
		}
		void recomputeBounds(Sprite& sprite) {
			const math::Vec3f& position = sprite.transform.position;
			const math::Vec3f& scale = sprite.transform.scale;

			sprite.globalBounds.x = position.x;
			sprite.globalBounds.y = position.y;
			sprite.globalBounds.w = sprite.localBounds.w * scale.x;
			sprite.globalBounds.h = sprite.localBounds.h * scale.y;
		}

		void updateRenderData(Sprite& sprite) {
			sprite.renderData.renderElements[0].texture = sprite.texture->getID();

			VertexPositionColorTexture* vertices[] {
				&sprite.renderData.vertices[0],
				&sprite.renderData.vertices[1],
			    &sprite.renderData.vertices[2],
				&sprite.renderData.vertices[3]
			};

			if (!sprite.textureSource.isEmpty()) {
					computeRectangleTextureCoordinates(vertices,
													   sprite.textureSource, 
													   static_cast<float32>(sprite.texture->getWidth()),
													   static_cast<float32>(sprite.texture->getHeight()));
			} else {
				applyDefaultRectangleTextureCoordinates(vertices);
			}

			updateGroupIdentifier(sprite);
		}
	}
}