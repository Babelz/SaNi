#include "sani/graphics/renderables/sprite.hpp"
#include "sani/graphics/vertex_helper.hpp"
#include "sani/resource/texture2d.hpp"

namespace sani {

	namespace graphics {

		Sprite::Sprite(resource::Texture2D* const texture, const float32 x, const float32 y, const float32 h, const float32 w) : Renderable(4, 6, 1) {
			assert(texture != nullptr);

			color = color::white;

			localBounds.w = w;
			localBounds.h = h;

			VertexPositionColorTexture* vertices[] {
				&renderData.vertices[0],
				&renderData.vertices[1],
				&renderData.vertices[2],
				&renderData.vertices[3]
			};

			applyDefaultRectangleTextureCoordinates(vertices);

			transform.position.x = x;
			transform.position.y = y;

			transform.origin.x = localBounds.w / 2.0f;
			transform.origin.y = localBounds.h / 2.0f;

			RenderElementData& spriteRenderData = renderData.renderElements[0];
			spriteRenderData.first = 0;
			spriteRenderData.last = 3;
			spriteRenderData.vertexElements = 9;
			spriteRenderData.offset = 0;
			spriteRenderData.indices = 6;

			recomputeBounds(*this);
			recomputeVertices(*this);
			updateRenderData(*this);
		}
		Sprite::Sprite(resource::Texture2D* const texture, const math::Vec2f& position, const math::Vec2f& size)
			: Sprite(texture, position.x, position.y, size.y, size.x) {
		}
		Sprite::Sprite(resource::Texture2D* const texture, const math::Rectf& bounds)
			: Sprite(texture, bounds.x, bounds.y, bounds.h, bounds.w) {
		}
		Sprite::Sprite(resource::Texture2D* const texture, const math::Vec2f& size)
			: Sprite(texture, 0.0f, 0.0f, size.y, size.x) {
		}
		Sprite::Sprite(resource::Texture2D* const texture)
			: Sprite(texture, 0.0f, 0.0f, static_cast<float32>(texture->getHeight()), static_cast<float32>(texture->getWidth())) {
		}
	}
}