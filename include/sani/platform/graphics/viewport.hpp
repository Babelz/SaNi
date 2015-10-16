#pragma once

#include "sani/types.hpp"

namespace sani {
	namespace graphics {
		
		/// @class Viewport viewport.hpp "sani/platform/viewport.hpp"
		/// @author voidbab
		/// 
		/// Basic viewport implementation.
		struct Viewport {
			uint32 x;
			uint32 y;

			uint32 width;
			uint32 height;

			Viewport(const uint32 x, const uint32 y, const uint32 width, const uint32 height);
			Viewport(const Viewport& viewport);
			Viewport();

			~Viewport();

			Viewport& operator =(const Viewport& rhs);
		};
	}
}

