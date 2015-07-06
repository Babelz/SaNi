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
			Window(const HINSTANCE& hInstance, const uint32 width, const uint16 height);
			
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
			void setSize(const uint32 width, const uint32 height);
			void setWidth(const uint32 width);
			void setHeight(const uint32 height);

			/// Set the position of the window.
			void setPosition(const uint32 x, const uint32 y);
			void setX(const uint32 x);
			void setY(const uint32 y);

			inline uint32 getX() const;
			inline uint32 getY() const;

			void getClientBounds(math::Rectu32& rect) const;
			void getWindowBounds(math::Rectu32& rect) const;
#endif

			inline uint32 getWidth();
			inline uint32 getHeight();

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

