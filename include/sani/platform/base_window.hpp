#pragma once

#include "sani/precompiled.hpp"

namespace sani {
	namespace graphics {

		/// @class Window base_window.hpp "sani/graphics/base_window.hpp"
		/// @author voidbab
		/// 
		/// Represents a common render window.
		class Window {
		private:
			String title;
		public:
			Window(const String& title);

			virtual int getX() const = 0;
			virtual int getY() const = 0;

			virtual uint32 getWidth() const = 0;
			virtual uint32 getHeight() const = 0;

			virtual void* getHandle() const = 0;

			virtual ~Window();
		};
	}
}


