#pragma once
#include "sani/types.hpp"
#include "sani/resource/resource_item.hpp"

#include "sani/forward_declare.hpp"
SANI_FORWARD_DECLARE_2(sani, resource, FontDescription);

namespace sani {
	namespace resource {
		class SpriteFontContent : public ResourceItem {
		private:
			FontDescription* description;
		public:
			SpriteFontContent(FontDescription* desc);
			~SpriteFontContent();
		};
	}
}