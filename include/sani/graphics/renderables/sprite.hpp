#pragma once

#include "sani/graphics/renderables/renderable.hpp"
#include "sani/forward_declare.hpp"

namespace sani {

	namespace graphics {

		SANI_FORWARD_DECLARE_2(sani, resource, Texture2D);

		/// @class Sprite sprite.hpp "sani/graphics/renderables/sprite.hpp"
		/// @author voidbab
		///
		/// Basic sprite class defined by transform, texture, effect and source.
		class Sprite final : public Renderable {
		public:
			Color color;

			resource::Texture2D* texture;

			Sprite(resource::Texture2D* const texture, const float32 x, const float32 y, const float32 h, const float32 w);
			Sprite(resource::Texture2D* const texture, const math::Vec2f& position, const math::Vec2f& size);
			Sprite(resource::Texture2D* const texture, const math::Rect32f& bounds);
			Sprite(resource::Texture2D* const texture, const math::Vec2f& size);
			Sprite(resource::Texture2D* const texture);
		};

		inline void recomputeVertices(Sprite& sprite);
		inline void recomputeBounds(Sprite& sprite);

		inline void updateRenderData(Sprite& sprite);
	}
}

#include "sani/graphics/inl/sprite.inl"