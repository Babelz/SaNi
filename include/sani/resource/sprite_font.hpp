#pragma once
#include "sani/resource/resource.hpp"

#include <vector>
#include "sani/forward_declare.hpp"
#include "sani/core/math/rectangle.hpp"

#include "sani/forward_declare.hpp"
SANI_FORWARD_DECLARE_2(sani, resource, Texture2D);

namespace sani {
	namespace resource {
		class SpriteFont : public Resource {
		private:
			typedef std::vector<unsigned short> Characters;
			typedef sani::math::Rect32 Glyph;
			typedef std::vector<Glyph> Glyphs;
			Texture2D* texture;
			Characters characters;
			Glyphs glyphs;
		public:
			SpriteFont(Texture2D* texture, const Glyphs& glyphs);
			~SpriteFont();
		};
	}
}
