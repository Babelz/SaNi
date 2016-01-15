#pragma once

#include "sani/types.hpp"
#include "sani/resource/resource_item.hpp"
#include "sani/resource/serialization.hpp"
#include "sani/forward_declare.hpp"
#include "sani/core/math/rectangle.hpp"
#include <vector>

SANI_FORWARD_DECLARE_2(sani, resource, FontDescription);
SANI_FORWARD_DECLARE_2(sani, resource, BitmapContent);
SANI_FORWARD_DECLARE_3(sani, resource, reader, SpriteFontReader);

namespace sani {

	namespace resource {

		class SpriteFontContent : public ResourceItem {
		private:
			using Glyph		 = math::Rect32i;
			using Glyphs	 = std::vector<Glyph>;
			using Characters = std::vector<unsigned short>;

			FontDescription* description;
			BitmapContent* texture;
			Glyphs glyphs;
			Characters characters;
		public:
			SpriteFontContent(FontDescription* desc, BitmapContent* texture, const Glyphs& glyphs, const Characters& characters);

			FontDescription* getDescription() const;

			BitmapContent* getTexture() const;

			const Glyphs& getGlyphs() const;

			const Characters& getCharacters() const;

			~SpriteFontContent();
		};
	}
}

SANI_DESERIALIZABLE_WITH(sani::resource::SpriteFontContent, sani::resource::reader::SpriteFontReader);