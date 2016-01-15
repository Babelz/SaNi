#pragma once
#include "sani/resource/resource.hpp"

#include <vector>
#include "sani/forward_declare.hpp"
#include "sani/core/math/rectangle.hpp"

#include "sani/forward_declare.hpp"
SANI_FORWARD_DECLARE_2(sani, resource, Texture2D);
SANI_FORWARD_DECLARE_2(sani, graphics, GraphicsDevice);

namespace sani {
	namespace resource {
		struct GlyphContent;
		class SpriteFont : public Resource {
			// TODO DEMO HAX
		public:
			using Characters = std::vector<uint32>;
			using Glyphs = std::vector<GlyphContent>;
			Texture2D* texture;
			Characters characters;
			Glyphs glyphs;
		public:
			SpriteFont(Texture2D* texture, const Glyphs& glyphs);
			~SpriteFont();
		};
	}
}
