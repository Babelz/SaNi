#include "sani/graphics/vertex_helper.hpp"
#include "sani/core/math/vector3.hpp"

namespace sani {

	namespace graphics {

		void applyRotationToTopLeftVertex(sani::math::Vec3f* const globalPosition, const sani::math::Vec3f* const vertexPosition, const float32 dx, const float32 dy, const float32 sin, const float32 cos) {
			globalPosition->x = globalPosition->x + (dx + vertexPosition->x) * cos - dy * sin;
			globalPosition->y = globalPosition->y + (dx + vertexPosition->x) * sin + dy * cos;
		}
		
		void applyRotationToTopRightVertex(sani::math::Vec3f* const globalPosition, const sani::math::Vec3f* const vertexPosition, const float32 dx, const float32 dy, const float32 sin, const float32 cos) {
			globalPosition->x = globalPosition->x + (dx + vertexPosition->x) * cos - dy * sin;
			globalPosition->y = globalPosition->y + (dx + vertexPosition->x) * sin + dy * cos;
		}
		
		void applyRotationToBottomLeftVertex(sani::math::Vec3f* const globalPosition, const sani::math::Vec3f* const vertexPosition, const float32 dx, const float32 dy, const float32 sin, const float32 cos) {
			globalPosition->x = globalPosition->x + dx * cos - (dy + vertexPosition->y) * sin;
			globalPosition->y = globalPosition->y + dx * sin + (dy + vertexPosition->y) * cos;
		}

		void applyRotationToBottomRightVertex(sani::math::Vec3f* const globalPosition, const sani::math::Vec3f* const vertexPosition, const float32 dx, const float32 dy, const float32 sin, const float32 cos) {
			globalPosition->x = globalPosition->x + (dx + vertexPosition->x) * cos - (dy + vertexPosition->y) * sin;
			globalPosition->y = globalPosition->y + (dx + vertexPosition->x) * sin + (dy + vertexPosition->y) * cos;
		}

		void applyRotationToTriangle(sani::math::Vec3f* const globalPositions, const sani::math::Vec3f* const vertexPositions, const float32 dx, const float32 dy, const float32 sin, const float32 cos) {
			applyRotationToTopLeftVertex	(&globalPositions[0], &vertexPositions[0], dx, dy, sin, cos);
			applyRotationToBottomLeftVertex	(&globalPositions[1], &vertexPositions[1], dx, dy, sin, cos);
			applyRotationToBottomRightVertex(&globalPositions[2], &vertexPositions[2], dx, dy, sin, cos);
		}

		void applyRotationToRectangle(sani::math::Vec3f* const globalPositions, const sani::math::Vec3f* const vertexPositions, const float32 dx, const float32 dy, const float32 sin, const float32 cos) {
			applyRotationToTopLeftVertex	(&globalPositions[0], &vertexPositions[0], dx, dy, sin, cos);
			applyRotationToTopRightVertex	(&globalPositions[1], &vertexPositions[1], dx, dy, sin, cos);
			applyRotationToBottomLeftVertex	(&globalPositions[2], &vertexPositions[2], dx, dy, sin, cos);
			applyRotationToBottomRightVertex(&globalPositions[3], &vertexPositions[3], dx, dy, sin, cos);
		}

		void computeTopLeftTextureCoordinate(sani::math::Vec2f* const uv, const sani::math::Rectf* const textureSource, const float32 textureWidth, const float32 textureHeight) {
			uv->x = textureSource->left() / textureWidth;
			uv->y = -(-textureHeight + textureSource->top()) / textureHeight;
		}

		void computeTopRightTextureCoordinate(sani::math::Vec2f* const uv, const sani::math::Rectf* const textureSource, const float32 textureWidth, const float32 textureHeight) {
			uv->x = textureSource->right() / textureWidth;
			uv->y = -(-textureHeight + textureSource->top()) / textureHeight;
		}

		void computeBottomLeftTextureCoordinate(sani::math::Vec2f* const uv, const sani::math::Rectf* const textureSource, const float32 textureWidth, const float32 textureHeight) {
			uv->x = textureSource->left() / textureWidth;
			uv->y = -(-textureHeight + textureSource->bottom()) / textureHeight;
		}

		void computeBottomRightTextureCoordinate(sani::math::Vec2f* const uv, const sani::math::Rectf* const textureSource, const float32 textureWidth, const float32 textureHeight) {
			uv->x = textureSource->right() / textureWidth;
			uv->y = -(-textureHeight + textureSource->bottom()) / textureHeight;
		}

		void computeRectangleTextureCoordinates(sani::math::Vec2f** const uvs, const sani::math::Rectf* const textureSource, const float32 textureWidth, const float32 textureHeight) {
			sani::math::Vec2f* const topLeft = uvs[0];
			computeTopLeftTextureCoordinate(topLeft, textureSource, textureWidth, textureHeight);

			sani::math::Vec2f* const topRight = uvs[1];
			computeTopRightTextureCoordinate(topRight, textureSource, textureWidth, textureHeight);

			sani::math::Vec2f* const bottomLeft = uvs[2];
			computeBottomLeftTextureCoordinate(bottomLeft, textureSource, textureWidth, textureHeight);

			sani::math::Vec2f* const bottomRight = uvs[3];
			computeBottomRightTextureCoordinate(bottomRight, textureSource, textureWidth, textureHeight);
		}

		void computeTriangleTextureCoordinates(sani::math::Vec2f** const uvs, const sani::math::Rectf* const textureSource, const float32 textureWidth, const float32 textureHeight) {
			sani::math::Rectf const topSource(textureSource->x + textureSource->w * 0.5f,
											  textureSource->y,
											  textureSource->h,
											  textureSource->w);
			
			sani::math::Vec2f* const top = uvs[0];
			computeTopLeftTextureCoordinate(top, &topSource, textureWidth, textureHeight);
			
			sani::math::Vec2f* const left = uvs[1];
			computeBottomLeftTextureCoordinate(left, textureSource, textureWidth, textureHeight);

			sani::math::Vec2f* const right = uvs[2];
			computeBottomRightTextureCoordinate(right, textureSource, textureWidth, textureHeight);
		}
	}
}