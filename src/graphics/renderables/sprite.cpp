#include "sani/graphics/renderables/sprite.hpp"
#include "sani/graphics/vertex_helper.hpp"

namespace sani {

	namespace graphics {

		Sprite::Sprite(sani::resource::Texture2D* const texture, const math::Vec2f& position, const math::Vec2f& size) : Renderable(4, 6, 1) {
			color = color::white;

			localBounds.w = size.x;
			localBounds.h = size.y;

			VertexPositionColorTexture* vertices[] {
				&renderData.vertices[0],
				&renderData.vertices[1],
				&renderData.vertices[2],
				&renderData.vertices[3]
			};

			applyDefaultRectangleTextureCoordinates(vertices);
		}
		Sprite::Sprite(sani::resource::Texture2D* const texture, const math::Rectf& bounds) : Renderable(0, 0, 0)  {
		}
		Sprite::Sprite(sani::resource::Texture2D* const texture, const math::Vec2f& size) : Renderable(0, 0, 0){
		}
		Sprite::Sprite(sani::resource::Texture2D* const texture) : Renderable(0, 0, 0) {
		}
	}
}