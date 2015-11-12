#include "sani/graphics/renderables/circle.hpp"
#include "sani/core/math/trigonometric.hpp"
#include "sani/graphics/vertex_helper.hpp"
#include "sani/graphics/renderer.hpp"

namespace sani {

	namespace graphics {

		void recomputeGeometryData(Circle& circle) {
			// TODO: optimize.

			recomputeBounds(circle);
			recomputeVertices(circle);
		}
		void recomputeVertices(Circle& circle) {
			const sani::math::Vec3f& position = circle.transform.position;
			const sani::math::Vec3f& origin = circle.transform.origin;
			const sani::math::Vec3f& scale = circle.transform.scale;
			const float32 rotation = circle.transform.rotation;

			/*
				TODO: borders, rotation.
			*/

			const float32 sin = sani::math::sin(rotation);
			const float32 cos = sani::math::cos(rotation);

			const float32 dx = -origin.x * scale.x;
			const float32 dy = -origin.y * scale.y;

			for (uint32 i = 0; i < circle.shapeVertices.size(); i++) {
				const float32 percent = (i / float(circle.shapeVertices.size() - 1));
				const float32 radius = static_cast<float32>(percent * 2.0f * PI);

				const float32 ox = origin.x + circle.radius * scale.x * sani::math::cos(radius);
				const float32 oy = origin.y + circle.radius * scale.y * sani::math::sin(radius);

				sani::math::Vec3f globalPosition = position;
				sani::math::Vec3f vertexPosition(ox, oy, position.z);

				applyRotationToBottomRightVertex(&globalPosition, &vertexPosition, dx, dy, sin, cos);

				VertexPositionColorTexture& vertex = circle.shapeVertices[i];
				vertex.vertexPositionColor.position = globalPosition;
				vertex.vertexPositionColor.color = circle.fill;
			}

			if (circle.borderThickness > 0.0f) {
				const float32 borderRadius = circle.radius + circle.borderThickness;

				for (uint32 i = 0; i < circle.borderVertices.size(); i++) {
					const float32 percent = (i / float(circle.borderVertices.size()));
					const float32 radius = static_cast<float32>(percent * 2.0f * PI);

					const float32 ox = origin.x + borderRadius * scale.x * sani::math::cos(radius);
					const float32 oy = origin.y + borderRadius * scale.y * sani::math::sin(radius);

					sani::math::Vec3f globalPosition = position;
					sani::math::Vec3f vertexPosition(ox, oy, position.z);

					applyRotationToBottomRightVertex(&globalPosition, &vertexPosition, dx, dy, sin, cos);

					VertexPositionColorTexture& vertex = circle.borderVertices[i];
					vertex.vertexPositionColor.position = globalPosition;
					vertex.vertexPositionColor.color = circle.borderFill;
				}
			}
		}
		void recomputeBounds(Circle& circle) {
			sani::math::Rectf localBounds;

			localBounds.x = 0.0f;
			localBounds.y = 0.0f;
			localBounds.w = circle.radius * 2.0f;
			localBounds.h = circle.radius * 2.0f;

			const sani::math::Vec3f& position = circle.transform.position;
			const sani::math::Vec3f& scale = circle.transform.scale;
			sani::math::Rectf globalBounds;

			globalBounds.x = position.x;
			globalBounds.y = position.y;
			globalBounds.w = localBounds.w * scale.x;
			globalBounds.h = localBounds.h * scale.y;

			circle.globalBounds = globalBounds;
			circle.localBounds = localBounds;
		}

		bool canRender(const Circle& circle, const Renderer& renderer) {
			const RenderState renderState	 =	circle.texture == nullptr ? RenderState::Polygons : RenderState::TexturedPolygons;
			const uint32 vertexElementsCount =	getVertexElementsCount(circle);

			return renderer.getVertexMode() == VertexMode::NoIndexing && renderer.getVertexElementsCount() == vertexElementsCount &&
				   renderer.getRenderState() == renderState;
		}
		void render(Circle& circle, Renderer& renderer) {
			// TODO: add texturing.
			if (circle.borderThickness > 0.0f) {
				for (const VertexPositionColorTexture vertex : circle.borderVertices) {
					const VertexPositionColor& vpc = vertex.vertexPositionColor;

					float32 vertexData[] =
					{
						vpc.position.x,
						vpc.position.y,
						vpc.position.z,

						vpc.color.r,
						vpc.color.g,
						vpc.color.b,
						vpc.color.a
					};

					renderer.renderPolygons(vertexData, 7);
				}
			}

			for (const VertexPositionColorTexture vertex : circle.shapeVertices) {
				const VertexPositionColor& vpc = vertex.vertexPositionColor;

				float32 vertexData[] = 
				{
					vpc.position.x,
					vpc.position.y,
					vpc.position.z,

					vpc.color.r,
					vpc.color.g,
					vpc.color.b,
					vpc.color.a
				};

				renderer.renderPolygons(vertexData, 7);
			}
		}

		const uint32 getVertexElementsCount(const Circle& circle) {
			return circle.texture == nullptr ? 7 : 9;
		}
	}
}