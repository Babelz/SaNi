#pragma once

#include "sani/platform/platform_config.hpp"
#include "sani/types.hpp"

namespace sani {

	// Primitive structure to hold bounds data.
	struct Bounds final {
		int32 x;
		int32 y;
		uint32 w;
		uint32 h;

		Bounds() = default;
		~Bounds() = default;
	};

	// Generate error if platform not valid. Console should only be used while 
	// debugging.
#if SANI_TARGET_PLATFORM == SANI_PLATFORM_WIN32 || SANI_TARGET_PLATFORM == SANI_PLATFORM_LINUX

	/// Opens the system console with given size and moves it to the given location.
	void openSystemConsole(const uint32 width, const uint32 height, const int32 x, const int32 y);
	/// Opens the system console with given width and height.
	void openSystemConsole(const uint32 width, const uint32 height);
	
	/// Moves the console to given location.
	void moveSystemConsole(const int32 x, const int32 y);
	
	/// Hides the system console.
	void hideSystemConsole();
	/// Hides and disposes the system console.
	void closeSystemConsole();

	Bounds getSystemConsoleBounds();
#else
	#error "Console not supported on the target platform"
#endif
}