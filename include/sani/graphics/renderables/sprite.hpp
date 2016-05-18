#pragma once

#include "sani/graphics/renderables/renderable.hpp"

SANI_FORWARD_DECLARE_2(sani, resource, Texture);

namespace sani {

	namespace graphics {

		/// @class Sprite sprite.hpp "sani/graphics/renderables/sprite.hpp"
		/// @author voidbab
		///
		/// Basic sprite class defined by transform, texture, effect and source.
		class Sprite : public Renderable {
		public:
			Color color;

			Sprite(Texture* const texture, const float32 x, const float32 y, const float32 w, const float32 h);
			Sprite(Texture* const texture, const math::Vec2f& position, const math::Vec2f& size);
			Sprite(Texture* const texture, const math::Rect32f& bounds);
			Sprite(Texture* const texture, const math::Vec2f& size);
			Sprite(Texture* const texture);

			virtual ~Sprite() = default;
		};

		inline void recomputeVertices(Sprite& sprite);
		inline void recomputeBounds(Sprite& sprite);

		inline void updateRenderData(Sprite& sprite);
	}
}

#include "sani/graphics/inl/sprite.inl"