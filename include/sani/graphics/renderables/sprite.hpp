#pragma once

#include "sani/graphics/renderables/renderable.hpp"
#include "sani/forward_declare.hpp"

namespace sani {

	namespace graphics {

		SANI_FORWARD_DECLARE_2(sani, resource, Texture2D);

		class Sprite : public Renderable {
		public:
			Color color;

			sani::resource::Texture2D* texture;

			Sprite(sani::resource::Texture2D* const texture);
		};

		inline void recomputeGeometryData(Sprite& sprite);
		inline void recomputeVertices(Sprite& sprite);
		inline void recomputeBounds(Sprite& sprite);

		inline void updateRenderData(Sprite& sprite);
	}
}