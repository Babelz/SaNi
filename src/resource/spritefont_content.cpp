#include "sani/resource/spritefont_content.hpp"
#include "sani/resource/font_description.hpp"
#include "sani/resource/bitmap_content.hpp"

namespace sani {

	namespace resource {

		SpriteFontContent::SpriteFontContent(FontDescription* desc, BitmapContent* texture, 
			const Glyphs& glyphs, const float32 lineSpacing) :  ResourceItem(), 
																description(desc), 
																texture(texture), 
																glyphs(glyphs),
																lineSpacing(lineSpacing) {
		}

		SpriteFontContent::~SpriteFontContent() { 
			delete texture;
		}

		FontDescription* SpriteFontContent::getDescription() const {
			return description;
		}

		BitmapContent* SpriteFontContent::getTexture() const {
			return texture;
		}

		const std::vector<GlyphContent>& SpriteFontContent::getGlyphs() const {
			return glyphs;
		}
	}
}