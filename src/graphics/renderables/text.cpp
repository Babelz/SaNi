#include "sani/graphics/renderables/text.hpp"
#include "sani/resource/sprite_font.hpp"

namespace sani {

	namespace graphics {

		Token::Token() : localRotation(0.0f), rect(0.0f, 0.0f, 0.0f, 0.0f), row(0), column(0), localScale(1.0f, 1.0f) {
		}
		
		Token::~Token() {
		}

		Text::Text(resource::SpriteFont* const font, const float32 x, const float32 y) 
			: font(font), Renderable(4, 6, 1) {

			SANI_ASSERT(font != nullptr);

			color = color::Red;

			transform.position.x = x;
			transform.position.y = y;
		}

		Text::~Text() {
		}
	}
}