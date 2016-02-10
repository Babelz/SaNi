#pragma once

#include "sani/types.hpp"

namespace sani {
	namespace graphics {
		
		/// @class Viewport viewport.hpp "sani/platform/viewport.hpp"
		/// @author voidbab
		/// 
		/// Basic viewport implementation.
		struct Viewport {
			int32 x;
			int32 y;

			uint32 width;
			uint32 height;

			Viewport(const int32 x, const int32 y, const uint32 width, const uint32 height);
			Viewport(const Viewport& viewport);
			Viewport();

			~Viewport();
		};
	}
}

