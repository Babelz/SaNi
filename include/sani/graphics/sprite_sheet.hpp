#pragma once

#include "sani/core/math/rectangle.hpp"
#include "sani/forward_declare.hpp"
#include "sani/types.hpp"

#include <vector>

SANI_FORWARD_DECLARE_2(sani, resource, Texture2D);

namespace sani {

	namespace graphics {

		/*
			TODO: loading from content.
		*/

		using SourceContainer = std::vector<math::Rectu32i>();

		/// @class SpriteSheet sprite_sheet.hpp "sani/graphics/sprite_sheet.hpp"
		/// @author voidbab
		///
		/// Sheet that uses index based lookup for the sources.
		class SpriteSheet {
		private:
			resource::Texture2D* const texture;
			SourceContainer sources;

			uint32 sourceWidth;
			uint32 sourceHeight;

			uint32 rows;
			uint32 columns;
		public:
			//// Creates new sprite sheet with given arguments.
			/// @param[in] texture texture that the sheet will be using
			/// @param[in] sourceWidth single sources width
			/// @param[in] sourceHeight single sources height
			SpriteSheet(resource::Texture2D* const texture, const uint32 sourceWidth, const uint32 sourceHeight);

			float32 getSourceWidth() const;
			float32 getSourceHeigt() const;

			uint32 getRowsCount() const;
			uint32 getColumnsCount() const;

			resource::Texture2D* const getTexture();
			
			const math::Rect32f& sourceAt(const uint32 row, const uint32 column) const;

			~SpriteSheet() = default;
		};
	}
}