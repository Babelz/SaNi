#pragma once

#include "sani/precompiled.hpp"

namespace sani {
	namespace graphics {

		/// @class Window base_window.hpp "sani/graphics/base_window.hpp"
		/// @author voidbab
		/// 
		/// Represents a common render window.
		class Window {
		public:
			Window();

			virtual int getX() const = 0;
			virtual int getY() const = 0;
			
			/// Return width of the window in pixels.
			/// @returns width of the window.
			virtual uint32 getWidth() const = 0;
			/// Return height of the window in pixels.
			/// @returns height of the window.
			virtual uint32 getHeight() const = 0;

			/// Return handle of this window. 
			/// Underlying data can differ between implementations.
			/// @returns void pointer to the handle.
			virtual void* getHandle() const = 0;

			virtual ~Window();
		};
	}
}


