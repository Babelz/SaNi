#pragma once
#include "sani/platform/graphics_precompiled.hpp"
#include "sani/platform/platform_config.hpp"

#if SANI_TARGET_PLATFORM == SANI_PLATFORM_WIN32

#include <Windows.h>

#endif

namespace sani {
	namespace graphics {
		
		// Forward declarations.
		class Color;

		/// @class Viewport graphics_device.hpp "sani/platform/graphics_device.hpp"
		/// @author voidbab
		/// 
		/// A virtual representation of the physical graphics adapter of this machine.
		/// DX contains WinDX and GL contains Linux and WinGL implementations.
		class GraphicsDevice {
		private:
			class Impl;

			Impl* impl;
		public:

			// Public Win32 members.
#if SANI_TARGET_PLATFORM == SANI_PLATFORM_WIN32

			GraphicsDevice(const HWND hWnd, const HINSTANCE hInstance);

			bool isFullscreen();
			void setFullscreen();
			void setWindowed();
#endif
			bool hasErrors() const;
			int8 getError() const;

			/// Sets the viewport of the device.
			/// @param[in] viewport viewport to use
			void setViewport(const Viewport& viewport);
			/// Returns the current viewport to the user.
			const Viewport& getViewport();

			/// Initializes the device.
			bool initialize();
			/// Cleans the device.
			bool cleanUp();

			/// Clears the device.
			void clear(const Color& color);
			/// Draws all contents of the device.
			void present();

			~GraphicsDevice();
		};
	}
}

