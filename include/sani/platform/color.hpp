#pragma once

#include "sani/precompiled.hpp"

namespace sani {
	namespace graphics {

		/// @class Color color.hpp "sani/platform/graphics/viewport.hpp"
		/// @author voidbab
		/// 
		/// Immutable 32-bit color.
		class Color {
			static const Color black;
			static const Color white;
			
			const int8 r;
			const int8 g;
			const int8 b;
			const int8 a;

			Color(const int8 r, const int8 g, const int8 b, const int8 a);
			Color(const Color& color, const int8 a);

			Color(const float32 r, const float32 g, const float32 b, const float32 a);
			Color(const Color& color, const float32 a);
			
			~Color();
		};
	}
}

