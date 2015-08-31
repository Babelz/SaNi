#pragma once

#include "sani/precompiled.hpp"

namespace sani {
	namespace graphics {
		
		/// @class Viewport viewport.hpp "sani/platform/viewport.hpp"
		/// @author voidbab
		/// 
		/// Basic viewport implementation.
		struct Viewport {
			const uint32 x;
			const uint32 y;
			
			const uint32 width;
			const uint32 height;

			Viewport(const uint32 x, const uint32 y, const uint32 width, const uint32 height);
			Viewport(const Viewport& viewport);
			Viewport();

			/// Returns true if all the components of the viewport are set to zero.
			bool isDefault() const;

			~Viewport();

			Viewport operator =(const Viewport& rhs);
		};
	}
}

