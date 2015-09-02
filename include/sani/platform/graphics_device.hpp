#pragma once
#include "sani/platform/graphics_precompiled.hpp"
#include "sani/platform/platform_config.hpp"

#include <stack>

#if SANI_TARGET_PLATFORM == SANI_PLATFORM_WIN32

#include <Windows.h>

#endif

namespace sani {
	namespace graphics {
		
		typedef std::stack<uint32> ErrorBuffer;

		// Forward declarations.
		struct Color;
		struct Viewport;

		/// @class GraphicsDevice graphics_device.hpp "sani/platform/graphics_device.hpp"
		/// @author voidbab
		/// 
		/// A virtual representation of the physical graphics adapter of this machine.
		/// DX contains WinDX and GL contains Linux and WinGL implementations.
		class GraphicsDevice {
		private:
			class Impl;

			Impl* impl;

			ErrorBuffer errorBuffer;

			void checkForErrors();
		public:

			// Public Win32 members.
#if SANI_TARGET_PLATFORM == SANI_PLATFORM_WIN32

			GraphicsDevice(const HWND hWnd, const HINSTANCE hInstance);

			bool isFullscreen() const;
			void setFullscreen();
			void setWindowed();
#endif
			/// Returns true if the error buffer contains errors.
			bool hasErrors() const;
			/// Returns the next error from the error buffer.
			uint32 getError();

			/// Sets the viewport of the device.
			/// @param[in] viewport viewport to use
			void setViewport(const Viewport& viewport);
			/// Returns the current viewport to the user.
			const Viewport& getViewport() const;

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

