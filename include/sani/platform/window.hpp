#pragma once

#include "platform_config.hpp"
#include "sani/precompiled.hpp"
#include "sani/forward_declare.hpp"

// Windows includes.
#if SANI_TARGET_PLATFORM == SANI_PLATFORM_WIN32

#include <Windows.h>

#endif

SANI_FORWARD_DECLARE_1(math, Rect32);

namespace sani {
	namespace graphics {
		
		/// @class window.hpp "sani/platform/graphics/window.hpp"
		/// @author voidbab
		///
		/// Represents a window.
		class Window {
		private:
			class Impl;

			Impl* impl;

			// Private Win32 members.
#if SANI_TARGET_PLATFORM == SANI_PLATFORM_WIN32

			static LRESULT CALLBACK WndProc(HWND hwnd, UINT msg, WPARAM wParam, LPARAM lParam);
#endif

		public:

			// Public Win32 members.
#if SANI_TARGET_PLATFORM == SANI_PLATFORM_WIN32

			Window(const HINSTANCE hInstance);

			inline HWND getHandle() const;
			
			/// Gets the title of the window.
			inline String getTitle() const;
			/// Sets the title of the window.
			void setTitle(const String& title);

			/// Minimizes the window.
			void minimize();
			/// Shows the window.
			void show();

			/// Set size of the window.
			void setSize(const int32 width, const int32 height);
			void setWidth(const int32 width);
			void setHeight(const int32 height);

			/// Set the position of the window.
			void setPosition(const int32 x, const int32 y);
			void setX(const int32 x);
			void setY(const int32 y);

			inline int32 getX() const;
			inline int32 getY() const;

			/// Returns coordinates of the window's client area.
			math::Rect32 getClientBounds() const;
			/// Returns the coordinates of the window's area.
			math::Rect32 getWindowBounds() const;

			/// Listens for windows events.
			void listen() const;
		
			/// Returns true if the window is still open.
			bool isOpen() const;
			
			/// Forces the window to close.
			void close();
#endif

			inline int32 getWidth();
			inline int32 getHeight();

			/// Initialize the window. Returns true 
			/// if no errors occurred during the
			/// initialization process of the window.
			bool initialize();

			~Window();
		};
	}
}

