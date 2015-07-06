#pragma once

#include "platform_config.hpp"
#include "sani/precompiled.hpp"

// Windows includes.
#if SANI_TARGET_PLATFORM == SANI_PLATFORM_WIN32
#include <windowsx.h>
#include <windows.h>
#include "sani/core/math/rectangle.hpp"
#endif

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
			static LRESULT CALLBACK WindowProc(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam);

			void moveWindow();
#endif

		public:
			// Public Win32 members.
#if SANI_TARGET_PLATFORM == SANI_PLATFORM_WIN32
			Window(const HINSTANCE& hInstance);
			
			const HWND& getHandle() const;
			
			/// Gets the title of the window.
			void getTitle(String& title) const;
			/// Sets the title of the window.
			void setTitle(const String& title);

			/// Hides the window.
			void hide();
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
#endif

			inline int32 getWidth();
			inline int32 getHeight();

			// TODO: implement get bounds and get client bounds
			//		 once Recti class has been implemented.
			// 
			// inline void getBounds(Recti& bounds);
			// inline void getClientArea(Recti& bounds);

			bool initialize();

			~Window();
		};
	}
}

