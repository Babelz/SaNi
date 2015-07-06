#pragma once

#include "platform_config.hpp"
#include "sani/precompiled.hpp"

// Windows includes.
#if SANI_TARGET_PLATFORM == SANI_PLATFORM_WIN32
#include <windowsx.h>
#include <windows.h>
#endif

namespace sani {
	namespace graphics {
		
		/// @class window.hpp "sani/platform/graphics/window.hpp"
		/// @author voidbab
		///
		/// Window of the game.
		class Window {
		private:
			class Impl;

			Impl* impl;

#if SANI_TARGET_PLATFORM == SANI_PLATFORM_WIN32
			static LRESULT CALLBACK WindowProc(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam);
#endif

		public:
			// Windows members.
#if SANI_TARGET_PLATFORM == SANI_PLATFORM_WIN32
			Window(const HINSTANCE& hInstance, const uint32 width, const uint16 height);
			
			const HWND& getHandle() const;
			
			void setTitle(const String& title);
#endif

			const inline uint32 getWidth();
			const inline uint32 getHeight();

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

