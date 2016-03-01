#include "sani/resource/reader/resource_reader.hpp"
#include "sani/resource/reader/spritefont_reader.hpp"
#include "sani/resource/texture2d.hpp"
#include "sani/resource/sprite_font.hpp"
#include "sani/resource/spritefont_content.hpp"

namespace sani {

	namespace resource {

		namespace reader {

			namespace {
				auto &db = sani::rtti::TypeDatabase::getInstance();
			}

			void SpriteFontReader::RTTI_Init() {
				RTTI_REGISTER_TYPE(sani::resource::reader::ResourceTypeReader);
				RTTI_REGISTER_TYPE(sani::resource::reader::SpriteFontReader);
				RTTI_DECLARE_BASECLASSES(sani::resource::reader::SpriteFontReader, typeof(sani::resource::reader::ResourceTypeReader));
				RTTI_DEFAULT_DYNAMIC_CTOR(sani::resource::reader::SpriteFontReader);
			}

			SpriteFontReader::SpriteFontReader() {
			}

			SpriteFontReader::~SpriteFontReader() {
			}

			void* SpriteFontReader::read(ResourceReader* reader) {
				Texture2D* texture = reader->readObject<Texture2D>();
				std::vector<GlyphContent> glyphs;

				uint32 glyphCount = static_cast<uint32>(reader->read7BitEncodedInt());
				glyphs.reserve(glyphCount);

				for (uint32 i = 0; i < glyphCount; ++i) {
					glyphs.push_back(GlyphContent{ 0 });
					GlyphContent& glyph = glyphs.back();
					glyph.character = reader->readUint32();
					
					glyph.source = reader->readRectangle();
					
					glyph.xOffset = reader->readSingle();
					glyph.yOffset = reader->readSingle();
					glyph.xAdvance = reader->readSingle();
					
				}

				float32 lineSpacing = reader->readSingle();

				SpriteFont* out = new SpriteFont(texture, glyphs, lineSpacing);

				return out;
			}
		}
	}
}
