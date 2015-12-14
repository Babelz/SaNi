#pragma once
#include "sani/types.hpp"
#include "sani/resource/resource_item.hpp"
#include "sani/resource/serialization.hpp"
#include "sani/forward_declare.hpp"
SANI_FORWARD_DECLARE_2(sani, resource, FontDescription);
SANI_FORWARD_DECLARE_2(sani, resource, BitmapContent);
SANI_FORWARD_DECLARE_3(sani, resource, reader, SpriteFontReader);

namespace sani {
	namespace resource {
		class SpriteFontContent : public ResourceItem {
		private:
			FontDescription* description;
			BitmapContent* texture;
		public:
			SpriteFontContent(FontDescription* desc, BitmapContent* texture);
			~SpriteFontContent();

			FontDescription* getDescription() const;

			BitmapContent* getTexture() const;
		};
	}
}

SANI_DESERIALIZABLE_WITH(sani::resource::SpriteFontContent, sani::resource::reader::SpriteFontReader);