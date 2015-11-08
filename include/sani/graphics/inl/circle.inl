#include "sani/graphics/renderables/circle.hpp"
#include "sani/core/math/trigonometric.hpp"
#include "sani/graphics/renderer.hpp"

namespace sani {

	namespace graphics {

		void recomputeGeometryData(Circle& circle) {
			// TODO: optimize.

			recomputeBounds(circle);
			recomputeVertices(circle);
		}
		void recomputeVertices(Circle& circle) {
			const sani::math::Vec3f& position = circle.transform.getPosition();

			/*
				TODO: borders, rotation.
			*/

			for (uint32 i = 0; i < circle.shapeVertices.size(); i++) {
				const float32 percent = (i / float(circle.shapeVertices.size() - 1));
				const float32 radius = percent * 2.0f * PI;

				const float32 ox = circle.globalBounds.x + circle.radius + circle.radius * sani::math::cos(radius);
				const float32 oy = circle.globalBounds.y + circle.radius + circle.radius * sani::math::sin(radius);

				VertexPositionColorTexture& vertex = circle.shapeVertices[i];
				vertex.vertexPositionColor.position.x = ox;
				vertex.vertexPositionColor.position.y = oy;
				vertex.vertexPositionColor.position.z = position.z;

				vertex.vertexPositionColor.color = circle.fill;
			}
		}
		void recomputeBounds(Circle& circle) {
			sani::math::Rectf localBounds;

			localBounds.x = 0.0f;
			localBounds.y = 0.0f;
			localBounds.w = circle.radius * 2.0f;
			localBounds.h = circle.radius * 2.0f;

			const sani::math::Vec3f& position = circle.transform.getPosition();
			const sani::math::Vec3f& scale = circle.transform.getScale();
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

			int i = 0;

			for (VertexPositionColorTexture vertex: circle.shapeVertices) {
				const VertexPositionColor& vpc = vertex.vertexPositionColor;

				if (i == 0) {
					i = 1;
					continue;
				}

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