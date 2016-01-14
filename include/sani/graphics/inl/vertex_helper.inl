#include "sani/graphics/vertex_helper.hpp"

namespace sani {

	namespace graphics {

		void applyRotationToTopLeftVertex(math::Vec3f* const globalPosition, const math::Vec3f* const vertexPosition, const float32 dx, const float32 dy, const float32 sin, const float32 cos) {
			globalPosition->x = globalPosition->x + (dx + vertexPosition->x) * cos - dy * sin;
			globalPosition->y = globalPosition->y + (dx + vertexPosition->x) * sin + dy * cos;
		}
		
		void applyRotationToTopRightVertex(math::Vec3f* const globalPosition, const math::Vec3f* const vertexPosition, const float32 dx, const float32 dy, const float32 sin, const float32 cos) {
			globalPosition->x = globalPosition->x + (dx + vertexPosition->x) * cos - dy * sin;
			globalPosition->y = globalPosition->y + (dx + vertexPosition->x) * sin + dy * cos;
		}
		
		void applyRotationToBottomLeftVertex(math::Vec3f* const globalPosition, const math::Vec3f* const vertexPosition, const float32 dx, const float32 dy, const float32 sin, const float32 cos) {
			globalPosition->x = globalPosition->x + dx * cos - (dy + vertexPosition->y) * sin;
			globalPosition->y = globalPosition->y + dx * sin + (dy + vertexPosition->y) * cos;
		}

		void applyRotationToBottomRightVertex(math::Vec3f* const globalPosition, const math::Vec3f* const vertexPosition, const float32 dx, const float32 dy, const float32 sin, const float32 cos) {
			globalPosition->x = globalPosition->x + (dx + vertexPosition->x) * cos - (dy + vertexPosition->y) * sin;
			globalPosition->y = globalPosition->y + (dx + vertexPosition->x) * sin + (dy + vertexPosition->y) * cos;
		}

		void applyRotationToTriangle(math::Vec3f* const globalPositions, const math::Vec3f* const vertexPositions, const float32 dx, const float32 dy, const float32 sin, const float32 cos) {
			applyRotationToTopLeftVertex	(&globalPositions[0], &vertexPositions[0], dx, dy, sin, cos);
			applyRotationToBottomLeftVertex	(&globalPositions[1], &vertexPositions[1], dx, dy, sin, cos);
			applyRotationToBottomRightVertex(&globalPositions[2], &vertexPositions[2], dx, dy, sin, cos);
		}

		void applyRotationToRectangle(math::Vec3f* const globalPositions, const math::Vec3f* const vertexPositions, const float32 dx, const float32 dy, const float32 sin, const float32 cos) {
			applyRotationToTopLeftVertex	(&globalPositions[0], &vertexPositions[0], dx, dy, sin, cos);
			applyRotationToTopRightVertex	(&globalPositions[1], &vertexPositions[1], dx, dy, sin, cos);
			applyRotationToBottomLeftVertex	(&globalPositions[2], &vertexPositions[2], dx, dy, sin, cos);
			applyRotationToBottomRightVertex(&globalPositions[3], &vertexPositions[3], dx, dy, sin, cos);
		}

		void computeTopLeftTextureCoordinate(math::Vec2f* const uv, const math::Rectf* const textureSource, const float32 textureWidth, const float32 textureHeight) {
			uv->x = textureSource->left() / textureWidth;
			uv->y = -(-textureHeight + textureSource->top()) / textureHeight;
		}

		void computeTopRightTextureCoordinate(math::Vec2f* const uv, const math::Rectf* const textureSource, const float32 textureWidth, const float32 textureHeight) {
			uv->x = textureSource->right() / textureWidth;
			uv->y = -(-textureHeight + textureSource->top()) / textureHeight;
		}

		void computeBottomLeftTextureCoordinate(math::Vec2f* const uv, const math::Rectf* const textureSource, const float32 textureWidth, const float32 textureHeight) {
			uv->x = textureSource->left() / textureWidth;
			uv->y = -(-textureHeight + textureSource->bottom()) / textureHeight;
		}

		void computeBottomRightTextureCoordinate(math::Vec2f* const uv, const math::Rectf* const textureSource, const float32 textureWidth, const float32 textureHeight) {
			uv->x = textureSource->right() / textureWidth;
			uv->y = -(-textureHeight + textureSource->bottom()) / textureHeight;
		}

		void computeRectangleTextureCoordinates(math::Vec2f** const uvs, const math::Rectf* const textureSource, const float32 textureWidth, const float32 textureHeight) {
			math::Vec2f* const topLeft = uvs[0];
			computeTopLeftTextureCoordinate(topLeft, textureSource, textureWidth, textureHeight);

			math::Vec2f* const topRight = uvs[1];
			computeTopRightTextureCoordinate(topRight, textureSource, textureWidth, textureHeight);

			math::Vec2f* const bottomLeft = uvs[2];
			computeBottomLeftTextureCoordinate(bottomLeft, textureSource, textureWidth, textureHeight);

			math::Vec2f* const bottomRight = uvs[3];
			computeBottomRightTextureCoordinate(bottomRight, textureSource, textureWidth, textureHeight);
		}

		void computeTriangleTextureCoordinates(math::Vec2f** const uvs, const math::Rectf* const textureSource, const float32 textureWidth, const float32 textureHeight) {
			math::Rectf const topSource(textureSource->x + textureSource->w * 0.5f,
									    textureSource->y,
									    textureSource->h,
									    textureSource->w);
			
			math::Vec2f* const top = uvs[0];
			computeTopLeftTextureCoordinate(top, &topSource, textureWidth, textureHeight);
			
			math::Vec2f* const left = uvs[1];
			computeBottomLeftTextureCoordinate(left, textureSource, textureWidth, textureHeight);

			math::Vec2f* const right = uvs[2];
			computeBottomRightTextureCoordinate(right, textureSource, textureWidth, textureHeight);
		}

		void applyDefaultRectangleTextureCoordinates(VertexPositionColorTexture** const vertices) {
			VertexPositionColorTexture* topLeftVertex = vertices[0];
			topLeftVertex->textureCoordinates.x = 0.0f;
			topLeftVertex->textureCoordinates.y = 1.0f;

			VertexPositionColorTexture* topRightVertex = vertices[1];
			topRightVertex->textureCoordinates.x = 1.0f;
			topRightVertex->textureCoordinates.y = 1.0f;
			
			VertexPositionColorTexture* bottomLeftVertex = vertices[2];
			bottomLeftVertex->textureCoordinates.x = 0.0f;
			bottomLeftVertex->textureCoordinates.y = 0.0f;

			VertexPositionColorTexture* bottomRightVertex = vertices[3];
			bottomRightVertex->textureCoordinates.x = 1.0f;
			bottomRightVertex->textureCoordinates.y = 0.0f;
		}

		void applyDefaultCircleTextureCoordinates(VertexPositionColorTexture* const vertices, const float32 rotation, const float32 radius, const math::Rectf* const textureSource, const float32 textureWidth, const float32 textureHeight, const uint32 count) {
			// TODO: WIP, not sure if it works the right way...
			
			for (uint32 i = 1; i + 1 < count; i += 2) {
				const auto blFi = 2.0f * PI * i / count * 2.0f;
				const auto brFi = 2.0f * PI * (i + 1) / count * 2.0f;
				
				VertexPositionColorTexture* const bl = &vertices[i];
				VertexPositionColorTexture* const br = &vertices[i + 1];

				const float32 blX = cos(blFi + PI) + textureSource->left() / textureWidth;//+ textureSource->left() / textureWidth;
				const float32 blY = sin(blFi + PI) + textureSource->top() / textureHeight;

				bl->textureCoordinates.x = -blX * 0.5f + 0.5f; //-x * 0.5f + 0.5f;
				bl->textureCoordinates.y = blY * 0.5f + 0.5f; //y * 0.5f + 0.5f;

				const float32 brX = cos(brFi + PI) + textureSource->left() / textureWidth;
				const float32 brY = sin(brFi + PI) + textureSource->top() / textureHeight;

				br->textureCoordinates.x = -brX * 0.5f + 0.5f; //-x * 0.5f + 0.5f;
				br->textureCoordinates.y = brY * 0.5f + 0.5f; //y * 0.5f + 0.5f;
			}
		}
	}
}