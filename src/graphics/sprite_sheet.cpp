#include "sani/resource/texture2d.hpp"
#include "sani/graphics/sprite_sheet.hpp"
#include "sani/debug.hpp"

namespace sani {

	namespace graphics {

		SpriteSheet::SpriteSheet(resource::Texture2D* const texture, const uint32 sourceWidth, const uint32 sourceHeight)
			: texture(texture), sourceWidth(sourceWidth), sourceHeight(sourceHeight), 
			  rows(texture->getHeight() / sourceHeight),
			  columns(texture->getWidth() / sourceWidth) {

			const int32 sourcesAreaHeight = static_cast<int32>(texture->getHeight());
			const int32 sourcesAreaWidth = static_cast<int32>(texture->getWidth());

			sources.reserve(rows * columns);

			for (int32 i = rows; i > 0; i--) {
				for (int32 j = 0; j < columns; j++) {
					sources.push_back(math::Rect32f(static_cast<float32>(j * sourceWidth), 
													static_cast<float32>((i - 1) * sourceHeight), 
													static_cast<float32>(sourceWidth),
													static_cast<float32>(sourceHeight)));
				}
			}
		}
		SpriteSheet::SpriteSheet() : texture(nullptr),
									 sourceWidth(0),
									 sourceHeight(0),
									 rows(0),
									 columns(0) {
		}

		const math::Rect32f& SpriteSheet::sourceAt(const uint32 row, const uint32 column) const {
			SANI_ASSERT(row < rows);
			SANI_ASSERT(column < columns);

			return sources[columns * row + column];
		}
	}
}