#pragma once

#include "sani/types.hpp"

namespace sani {

	namespace graphics {

		/// @class Color color.hpp "sani/platform/graphics/viewport.hpp"
		/// @author voidbab
		/// 
		/// Mutable 32-bit color.
		struct Color {
			float32 r;
			float32 g;
			float32 b;
			float32 a;

			/// Creates new instance of the color object with given values. 255 base.
			Color(const uint8 r, const uint8 g, const uint8 b, const uint8 a);
			Color(const Color& color, const uint8 a);

			/// Creates new instance of the color object with given values. Values are multiplied by 255.
			Color(const float32 r, const float32 g, const float32 b, const float32 a);
			Color(const Color& color, const float32 a);

			Color();
			
			~Color();

			Color& operator =(const Color& rhs);
			bool operator ==(const Color& rhs);
			bool operator !=(const Color& rhs);
		};

		const Color black	(0.0f, 0.0f, 0.0f, 1.0f);
		const Color white	(1.0f, 1.0f, 1.0f, 1.0f);
		const Color red		(1.0f, 0.0f, 0.0f, 1.0f);
		const Color green	(0.0f, 1.0f, 0.0f, 1.0f);
		const Color blue	(0.0f, 0.0f, 1.0f, 1.0f);
	}
}

