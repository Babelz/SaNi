#pragma once

#include "sani/platform/platform_config.hpp"
#include "sani/precompiled.hpp"
#include "sani/core/events.h"

// Windows includes.
#if SANI_TARGET_PLATFORM == SANI_PLATFORM_WIN32

#include <Windows.h>

#endif

namespace sani {
	namespace graphics {
		
		/// @class Window "sani/platform/window.hpp"
		/// @author voidbab
		///
		/// Represents a window.
		class Window {
		private:
			// Forward declaration of common implementation living inside the 
			// impl class.
			class Cimpl;
			class Impl;

			Impl* impl;

			// Private Win32 members.
#if SANI_TARGET_PLATFORM == SANI_PLATFORM_WIN32

			static LRESULT CALLBACK WndProc(HWND hwnd, UINT msg, WPARAM wParam, LPARAM lParam);
#endif

		public:

			// Public Win32 members.
#if SANI_TARGET_PLATFORM == SANI_PLATFORM_WIN32

			// Called when the window is being closed.
			SANI_DECLARE_EVENT(onClosing, void(Window&));
			// Called when the window is closed.
			SANI_DECLARE_EVENT(onClosed, void(Window&));
			// Called when the window is being minimized.
			SANI_DECLARE_EVENT(onMinimize, void(Window&));
			// Called when the window is returned to the windowed mode.
			SANI_DECLARE_EVENT(onWindowed, void(Window&));
			// Called when the window is returned to the fullscreen mode.
			SANI_DECLARE_EVENT(onFullscreen, void(Window&));
			// Called when the window gets moved.
			SANI_DECLARE_EVENT(onMoved, void(Window&, int, int, int, int));
			// Called when the window gets resized.
			SANI_DECLARE_EVENT(onResize, void(Window&, int, int, int, int));

			Window(const HINSTANCE hInstance, const uint32 width, const uint32 height);

			HWND getHandle() const;
			
			/// Gets the title of the window.
			String getTitle() const;
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

			int32 getX() const;
			int32 getY() const;

			uint32 getClientWidth() const;
			uint32 getClientHeight() const;

			/// Listens for windows events.
			void listen() const;
		
			/// Returns true if the window is still open.
			bool isOpen() const;
			
			/// Forces the window to close.
			void close();
#endif

			int32 getWidth();
			int32 getHeight();

			/// Initialize the window. Returns true 
			/// if no errors occurred during the
			/// initialization process of the window.
			bool initialize();

			~Window();
		};
	}
}

