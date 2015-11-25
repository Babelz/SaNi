#include "sani/graphics/renderables/circle.hpp"
#include "sani/core/math/trigonometric.hpp"
#include "sani/graphics/vertex_helper.hpp"
#include "sani/graphics/render_helper.hpp"
#include "sani/graphics/renderer.hpp"

namespace sani {

	namespace graphics {

		void recomputeVertices(Circle& circle) {
			const math::Vec3f& position = circle.transform.position;
			const math::Vec3f& origin = circle.transform.origin;
			const math::Vec3f& scale = circle.transform.scale;
			const float32 rotation = circle.transform.rotation;

			/*
				TODO: borders, rotation.
			*/

			const float32 sin = math::sin(rotation);
			const float32 cos = math::cos(rotation);

			const float32 dx = -origin.x * scale.x;
			const float32 dy = -origin.y * scale.y;

			RenderElementData& shapeRenderData = circle.renderData.renderElements[0];

			VertexPositionColorTexture& shapeCenter = circle.renderData.vertices[0];
			shapeCenter.vertexPositionColor.position.x = circle.globalBounds.x;
			shapeCenter.vertexPositionColor.position.y = circle.globalBounds.y;
			shapeCenter.vertexPositionColor.position.z = position.z;
			shapeCenter.vertexPositionColor.color = circle.fill;

			for (uint32 i = 1; i < shapeRenderData.last + 1; i++) {
				const float32 percent = (i / float32(circle.vertices));
				const float32 radius = percent * 2.0f * PI;

				const float32 ox = origin.x + circle.radius * scale.x * math::cos(radius);
				const float32 oy = origin.y + circle.radius * scale.y * math::sin(radius);

				math::Vec3f globalPosition = position;
				math::Vec3f vertexPosition(ox, oy, position.z);

				applyRotationToBottomRightVertex(&globalPosition, &vertexPosition, dx, dy, sin, cos);

				VertexPositionColorTexture& vertex = circle.renderData.vertices[i];
				vertex.vertexPositionColor.position = globalPosition;
				vertex.vertexPositionColor.color = circle.fill;
			}

			if (circle.borderThickness > 0.0f) {
				RenderElementData& borderRenderData = circle.renderData.renderElements[1];

				const float32 borderRadius = circle.radius + circle.borderThickness;

				VertexPositionColorTexture& borderCenter = circle.renderData.vertices[borderRenderData.first];
				borderCenter = shapeCenter;

				for (uint32 i = borderRenderData.first; i < borderRenderData.last + 1; i++) {
					const float32 percent = (i / float32(circle.vertices));
					const float32 radius = percent * 2.0f * PI;

					const float32 ox = origin.x + borderRadius * scale.x * math::cos(radius);
					const float32 oy = origin.y + borderRadius * scale.y * math::sin(radius);

					math::Vec3f globalPosition = position;
					math::Vec3f vertexPosition(ox, oy, position.z);

					applyRotationToBottomRightVertex(&globalPosition, &vertexPosition, dx, dy, sin, cos);

					VertexPositionColorTexture& vertex = circle.renderData.vertices[i];
					vertex.vertexPositionColor.position = globalPosition;
					vertex.vertexPositionColor.color = circle.borderFill;
				}
			}
 		}
		void recomputeBounds(Circle& circle) {
			circle.localBounds.x = 0.0f;
			circle.localBounds.y = 0.0f;
			circle.localBounds.w = circle.radius * 2.0f;
			circle.localBounds.h = circle.radius * 2.0f;

			const math::Vec3f& position = circle.transform.position;
			const math::Vec3f& scale = circle.transform.scale;
			
			circle.globalBounds.x = position.x;
			circle.globalBounds.y = position.y;
			circle.globalBounds.w = circle.localBounds.w * scale.x;
			circle.globalBounds.h = circle.localBounds.h * scale.y;
		}

		void updateRenderData(Circle& circle) {
			setupShapeForRendering(&circle, circle.borderThickness);
		}
	}
}