#pragma once
#include "sani/resource/resource.hpp"

#include <vector>
#include "sani/forward_declare.hpp"
#include "sani/core/math/rectangle.hpp"

#include "sani/forward_declare.hpp"

SANI_FORWARD_DECLARE_2(sani, resource, Texture2D);
SANI_FORWARD_DECLARE_2(sani, graphics, GraphicsDevice);

namespace sani {
	
	namespace resource {

		// TODO: Demo hax, fix.
		class SpriteFont : public Resource {
		public:
			using Characters = std::vector<uint16>;
			using Glyph		 = sani::math::Rect32i;
			using Glyphs     = std::vector<Glyph>;
			
			Texture2D* texture;
			Characters characters;
			Glyphs glyphs;
		public:
			SpriteFont(Texture2D* texture, const Glyphs& glyphs, const Characters& characters);

			void createStaticText(const String& text, graphics::GraphicsDevice* device);

			~SpriteFont();
		};
	}
}
