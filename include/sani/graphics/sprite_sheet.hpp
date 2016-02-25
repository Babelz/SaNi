#pragma once

#include "sani/core/math/rectangle.hpp"
#include "sani/forward_declare.hpp"
#include "sani/types.hpp"

#include <vector>

SANI_FORWARD_DECLARE_2(sani, graphics, Texture2D);

namespace sani {

	namespace graphics {

		using SourceContainer = std::vector<math::Rect32f>();

		/// @class SpriteSheet sprite_sheet.hpp "sani/graphics/sprite_sheet.hpp"
		/// @author voidbab
		///
		/// Sheet that uses index based lookup for the sources.
		class SpriteSheet {
		private:
			Texture2D* const texture;
			SourceContainer sources;

			const float32 sourceWidth;
			const float32 sourceHeight;

			const uint32 rows;
			const uint32 columns;
		public:
			//// Creates new sprite sheet with given arguments.
			/// @param[in] texture texture that the sheet will be using
			/// @param[in] sourceWidth single sources width
			/// @param[in] sourceHeight single sources height
			/// @param[in] xOffset offset applied to x 
			/// @param[in] yOffset offset applied to y
			SpriteSheet(Texture2D* const texture, const float32 sourceWidth, const float32 sourceHeight, const float32 xOffset, const float32 yOffset);
			
			//// Creates new sprite sheet with given arguments.
			/// @param[in] texture texture that the sheet will be using
			/// @param[in] sourceWidth single sources width
			/// @param[in] sourceHeight single sources height
			SpriteSheet(Texture2D* const texture, const float32 sourceWidth, const float32 sourceHeight);

			float32 getSourceWidth() const;
			float32 getSourceHeigt() const;

			uint32 getRowsCount() const;
			uint32 getColumnsCount() const;

			Texture2D* const getTexture();
			
			const math::Rect32f& sourceAt(const uint32 row, const uint32 column) const;

			~SpriteSheet() = default;
		};
	}
}