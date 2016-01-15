#include "sani/resource/sprite_font.hpp"
#include "sani/resource/texture2d.hpp"
#include "sani/platform/graphics/graphics_device.hpp"
#include "sani/resource/spritefont_content.hpp"
namespace sani {
	namespace resource {

		SpriteFont::SpriteFont(Texture2D* texture, const Glyphs& glyphs) 
			: texture(texture), glyphs(glyphs) {
			characters.reserve(glyphs.size());
			for (auto& g : glyphs) {
				characters.push_back(g.character);
			}
		}

		SpriteFont::~SpriteFont() {

		}

	}
}