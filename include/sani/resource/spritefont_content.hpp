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

		struct GlyphContent {
			uint32 character;
			sani::math::Recti source;
			float32 xOffset;
			float32 yOffset;
			float32 xAdvance;
		};

		class SpriteFontContent : public ResourceItem {
		private:
			using Glyphs = std::vector<GlyphContent>;
			using Characters = std::vector<uint32>;

			FontDescription* description;
			BitmapContent* texture;
			Glyphs glyphs;
			Characters characters;
		public:
			SpriteFontContent(FontDescription* desc, BitmapContent* texture, const Glyphs& glyphs);
			~SpriteFontContent();

			FontDescription* getDescription() const;

			BitmapContent* getTexture() const;

			const Glyphs& getGlyphs() const;
		};
	}
}

SANI_DESERIALIZABLE_WITH(sani::resource::SpriteFontContent, sani::resource::reader::SpriteFontReader);