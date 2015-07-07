#pragma once
#include "graphics_precompiled.hpp"
#include "sani/platform/platform_config.hpp"

#if SANI_TARGET_PLATFORM == SANI_PLATFORM_WIN32

#include <Windows.h>

#endif

namespace sani {
	namespace graphics {
		
		/// @class Viewport graphics_device.hpp "sani/platform/graphics/graphics_device.hpp"
		/// @author voidbab
		/// 
		/// A virtual representation of the physical graphics adapter of this machine.
		/// DX contains WinDX and GL contains Linux and WinGL implementations.
		class GraphicsDevice {
		private:
			class Impl;

			Impl* imp;
		public:

			// Public Win32 members.
#if SANI_TARGET_PLATFORM == SANI_PLATFORM_WIN32

			GraphicsDevice(const HWND hwnd);

#endif

			/// Returns true if device has errors.
			inline bool hasErrors() const;
			/// Returns the next error if device has errors.
			GraphicsErrorType getError();

			/// Sets the viewport of the device.
			/// @param[in] viewport viewport to use
			void setViewport(const Viewport& viewport);
			/// Returns the current viewport to the user.
			Viewport& getViewport();

			/// Initializes the device.
			void initialize();
			/// Cleans the device.
			void cleanUp();
			/// Clears the device.
			void clear();

			~GraphicsDevice();
		};
	}
}

