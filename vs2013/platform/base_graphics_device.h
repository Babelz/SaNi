#pragma once

#include "sani/precompiled.hpp"

namespace sani {
	namespace graphics {

		/// @class BaseGraphicsDevice base_graphics_device.hpp "sani/platform/graphics/base_graphics_device.hpp"
		/// @author voidbab
		///
		/// "Virtual" representation of the physical graphics adapter. Common interface used to
		/// wrap different graphics apis.
		class BaseGraphicsDevice {
		public:
			BaseGraphicsDevice();
			~BaseGraphicsDevice();
		};
	}
}

