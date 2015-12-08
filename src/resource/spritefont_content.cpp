#include "sani/resource/spritefont_content.hpp"
#include "sani/resource/font_description.hpp"

namespace sani {
	namespace resource {
		SpriteFontContent::SpriteFontContent(FontDescription* desc)
			: ResourceItem(), description(desc) {

		}

		SpriteFontContent::~SpriteFontContent() { }
	}
}