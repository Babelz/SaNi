#include "sani/resource/reader/resource_reader.hpp"
#include "sani/resource/reader/spritefont_reader.hpp"
#include "sani/resource/texture2d.hpp"
#include "sani/resource/sprite_font.hpp"

namespace sani {
	namespace resource {
		namespace reader {
			SpriteFontReader::SpriteFontReader() {}

			SpriteFontReader::~SpriteFontReader() {}

			void* SpriteFontReader::read(ResourceReader* reader) {
				Texture2D* texture = reader->readObject<Texture2D>();
				std::vector<sani::math::Rect32> glyphs;

				SpriteFont* out = new SpriteFont(texture, glyphs);

				return out;
			}
		}
	}
}
