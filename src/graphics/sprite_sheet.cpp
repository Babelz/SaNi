#include "sani/resource/texture2d.hpp"
#include "sani/graphics/sprite_sheet.hpp"
#include "sani/debug.hpp"

namespace sani {

	namespace graphics {

		//SpriteSheet::SpriteSheet(resource::Texture2D* const texture, const uint32 sourceWidth, const uint32 sourceHeight)
		//	: texture(texture), sourceWidth(sourceWidth), sourceHeight(sourceHeight) {
		//	
		//	SANI_ASSERT(texture != nullptr);

		//	const uint32 sourcesAreaHeight = texture->getHeight();
		//	const uint32 sourcesAreaWidth = texture->getWidth();

		//	rows = sourcesAreaHeight / sourceHeight + (sourcesAreaHeight & sourceHeight);
		//	columns = sourcesAreaWidth / sourceWidth + (sourcesAreaWidth & sourceWidth);
		//	
		//	for (uint32 i = 0; i < rows; i++) {
		//		for (uint32 j = 0; j < columns; j++) {
		//			sources.push_back(math::Rectu32i(j * sourceWidth, i * sourceHeight, sourceWidth, sourceHeight));
		//		}
		//	}
		//}

		//float32 SpriteSheet::getSourceWidth() const {
		//}
		//float32 SpriteSheet::getSourceHeigt() const {
		//}

		//uint32 SpriteSheet::getRowsCount() const {
		//}
		//uint32 SpriteSheet::getColumnsCount() const {
		//}

		//resource::Texture2D* const SpriteSheet::getTexture() {
		//}

		//const math::Rect32f& SpriteSheet::sourceAt(const uint32 row, const uint32 column) const {
		//}
	}
}