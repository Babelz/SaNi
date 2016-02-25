#pragma once

#include "sani/core/math/rectangle.hpp"
#include "sani/forward_declare.hpp"
#include "sani/types.hpp"

#include <vector>

SANI_FORWARD_DECLARE_2(sani, resource, Texture2D);

namespace sani {

	namespace graphics {

		/*
			TODO: should be loaded from content?
		*/

		using SourceContainer = std::vector<math::Rectu32i>;

		/// @class SpriteSheet sprite_sheet.hpp "sani/graphics/sprite_sheet.hpp"
		/// @author voidbab
		///
		/// Sheet that uses index based lookup for the sources.
		class SpriteSheet {
		public:
			resource::Texture2D* const texture;
			SourceContainer sources;

			const uint32 sourceWidth;
			const uint32 sourceHeight;

			const uint32 rows;
			const uint32 columns;

			//// Creates new sprite sheet with given arguments.
			/// @param[in] texture texture that the sheet will be using
			/// @param[in] sourceWidth single sources width
			/// @param[in] sourceHeight single sources height
			SpriteSheet(resource::Texture2D* const texture, const uint32 sourceWidth, const uint32 sourceHeight);

			const math::Rectu32i& sourceAt(const uint32 row, const uint32 column) const;

			~SpriteSheet() = default;
		};
	}
}