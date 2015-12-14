#include "sani/resource/spritefont_content.hpp"
#include "sani/resource/font_description.hpp"
#include "sani/resource/bitmap_content.hpp"
namespace sani {
	namespace resource {
		SpriteFontContent::SpriteFontContent(FontDescription* desc, BitmapContent* texture)
			: ResourceItem(), description(desc), texture(texture) {

		}

		SpriteFontContent::~SpriteFontContent() { }

		FontDescription* SpriteFontContent::getDescription() const {
			return description;
		}

		BitmapContent* SpriteFontContent::getTexture() const {
			return texture;
		}
	}
}