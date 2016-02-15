#include "sani/platform/platform_config.hpp"

#if SANI_TARGET_PLATFORM == SANI_PLATFORM_WIN32

#include "sani/platform/console.hpp"
#include "sani/debug.hpp"

#include <io.h>
#include <fcntl.h>
#include <Windows.h>

/*
	Win32 impl of the console functions.
*/

namespace sani {
	
	static bool consoleAllocated = false;

	static void allocateConsole() {
		AllocConsole();
		
		// Redirect out.
		HANDLE outHandle = GetStdHandle(STD_OUTPUT_HANDLE);
		int32 osfOutHandle = _open_osfhandle(reinterpret_cast<long>(outHandle), _O_TEXT);

		FILE* hfOut = _fdopen(osfOutHandle, "w");
		setvbuf(hfOut, NULL, _IONBF, 1);

		*stdout = *hfOut;

		// Redirect in.
		HANDLE inHandle = GetStdHandle(STD_INPUT_HANDLE);
		int32 osfInHandle = _open_osfhandle((long)inHandle, _O_TEXT);
		FILE* hfIn = _fdopen(osfInHandle, "r");
		setvbuf(hfIn, NULL, _IONBF, 128);
		
		*stdin = *hfIn;

		consoleAllocated = true;
	}
	static Bounds getBounds(Bounds& bounds) {
		LPRECT cRect;

		GetWindowRect(GetConsoleWindow(), cRect);

		bounds.x = cRect->left;
		bounds.y = cRect->top;
		bounds.w = cRect->right - cRect->left;
		bounds.h = cRect->bottom - cRect->top;
	}

	void openSystemConsole(const uint32 width, const uint32 height, const int32 x, const int32 y) { 	
		if (!consoleAllocated) allocateConsole();
	}
	void openSystemConsole(const uint32 width, const uint32 height) {
	}

	void moveSystemConsole(const int32 x, const int32 y) {
		SANI_ASSERT(consoleAllocated);

		LPRECT wndRect;
		
		GetWindowRect(GetConsoleWindow(), wndRect);
		
		MoveWindow(GetConsoleWindow(), x, y, wndRect->right - wndRect->left, wndRect->bottom - wndRect->top, true);
	}

	void hideSystemConsole() {
		SANI_ASSERT(consoleAllocated);

		ShowWindow(GetConsoleWindow(), SW_HIDE);
	}
	void closeSystemConsole() {
		SANI_ASSERT(consoleAllocated);

		if (FreeConsole()) {
			const DWORD error = GetLastError();
			
			throw std::runtime_error("something went wrong while closing the console, win32 error code " + error);
		}

		consoleAllocated = false;
	}


	Bounds getSystemConsoleBounds() {
		Bounds bounds;

		getBounds(bounds);

		return bounds;
	}
}

#endif