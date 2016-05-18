#pragma once

#include "sani/graphics/renderables/rectangle.hpp"
#include "sani/graphics/renderables/renderable.hpp"
#include "sani/forward_declare.hpp"
#include "sani/types.hpp"

SANI_FORWARD_DECLARE_2(sani, resource, SpriteFont);

namespace sani {

	namespace graphics {
		
		struct Token final {
			Rectangle		rect;
			
			math::Vec2f localPosition;
			math::Vec2f localScale;
			float32		localRotation;

			char16		ch;

			uint32 row;
			uint32 column;

			Token();
			~Token();
		};

		class Text final : public Renderable {
		public:
			std::vector<Token> tokens;

			resource::SpriteFont* font;
			
			String16 contents;
			Color color;

			Text(resource::SpriteFont* const font, const float32 x, const float32 y);
			~Text();
		};

		inline void setText(Text& staticText, const String16& contents, const Color& color);

		inline void recomputeVertices(Text& text);
		inline void recomputeBounds(Text& text);

		inline void updateRenderData(Text& text);
	}
}

#include "sani/graphics/inl/text.inl"