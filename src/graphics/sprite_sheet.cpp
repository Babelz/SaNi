#include "sani/resource/texture2d.hpp"
#include "sani/graphics/sprite_sheet.hpp"
#include "sani/debug.hpp"

namespace sani {

	namespace graphics {

		SpriteSheet::SpriteSheet(resource::Texture2D* const texture, const uint32 sourceWidth, const uint32 sourceHeight)
			: texture(texture), sourceWidth(sourceWidth), sourceHeight(sourceHeight), 
			  rows(texture->getHeight() / sourceHeight + (texture->getHeight() % sourceHeight)),
			  columns(texture->getWidth() / sourceWidth + (texture->getWidth() % sourceWidth)) {

			const uint32 sourcesAreaHeight = texture->getHeight();
			const uint32 sourcesAreaWidth = texture->getWidth();

			sources.reserve(rows * columns);

			for (uint32 i = 0; i < rows; i++) {
				for (uint32 j = 0; j < columns; j++) {
					sources.push_back(math::Rectu32i(j * sourceWidth, i * sourceHeight, sourceWidth, sourceHeight));
				}
			}
		}
		SpriteSheet::SpriteSheet() : texture(nullptr),
									 sourceWidth(0),
									 sourceHeight(0),
									 rows(0),
									 columns(0) {
		}

		const math::Rectu32i& SpriteSheet::sourceAt(const uint32 row, const uint32 column) const {
			SANI_ASSERT(row < rows);
			SANI_ASSERT(column < columns);

			return sources[columns * row + column];
		}
	}
}