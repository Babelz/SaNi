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
				std::vector<sani::math::Rect32i> glyphs;

				uint32 glyphCount = static_cast<uint32>(reader->read7BitEncodedInt());
				glyphs.reserve(glyphCount);

				for (uint32 i = 0; i < glyphCount; ++i) {
					math::Rect32i rect;
					rect.x = reader->readInt32();
					rect.y = reader->readInt32();
					rect.w = reader->readInt32();
					rect.h = reader->readInt32();
					glyphs.push_back(rect);
				}

				std::vector<unsigned short> characters;

				uint32 charCount = static_cast<uint32>(reader->read7BitEncodedInt());
				characters.reserve(charCount);

				for (uint32 i = 0; i < charCount; ++i) {
					characters.push_back(reader->readUint16());
				}

				SpriteFont* out = new SpriteFont(texture, glyphs, characters);

				return out;
			}
		}
	}
}
