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

		void computeRectangleTextureCoordinates(sani::math::Vec2f** const textureCoordinates, const sani::math::Rectf* const textureSource, const uint32 textureWidth, const uint32 textureHeight) {
			const float32 tw = static_cast<float32>(textureWidth);
			const float32 th = static_cast<float32>(textureHeight);
			
			const float32 sl = textureSource->left();
			const float32 sr = textureSource->right();

			sani::math::Vec2f& tl = *textureCoordinates[0];
			tl.x = sl / tw;
			tl.y = textureSource->y / th;

			sani::math::Vec2f& tr = *textureCoordinates[1];
			tr.x = sr / tw;
			tr.y = tl.y;

			sani::math::Vec2f& bl = *textureCoordinates[2];
			bl.x = sl / tw;
			bl.y = (textureSource->h + textureSource->y) / th;

			sani::math::Vec2f& br = *textureCoordinates[3];
			br.x = sr / tw;
			br.y = bl.y;
		}
	}
}