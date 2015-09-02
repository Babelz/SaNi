#pragma once

#include "sani/precompiled.hpp"

namespace sani {
	namespace graphics {

		/// @class Color color.hpp "sani/platform/graphics/viewport.hpp"
		/// @author voidbab
		/// 
		/// Mutable 32-bit color.
		struct Color {
			static const Color black;
			static const Color white;
			static const Color red;
			static const Color green;
			static const Color blue;
			
			uint8 r;
			uint8 g;
			uint8 b;
			uint8 a;

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
	}
}

