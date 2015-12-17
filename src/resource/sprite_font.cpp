#include "sani/resource/sprite_font.hpp"
#include "sani/resource/texture2d.hpp"
namespace sani {
	namespace resource {

		SpriteFont::SpriteFont(Texture2D* texture, const Glyphs& glyphs) 
			: texture(texture), glyphs(glyphs) {

		}

		SpriteFont::~SpriteFont() {

		}

	}
}