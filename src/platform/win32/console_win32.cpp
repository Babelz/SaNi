#include "sani/platform/platform_config.hpp"

#if SANI_TARGET_PLATFORM == SANI_PLATFORM_WIN32

#include "sani/platform/console.hpp"
#include "sani/debug.hpp"

#include <io.h>
#include <fcntl.h>
#include <Windows.h>
#include <sstream>
#include <iostream>
#include <stdlib.h>

#define _WIN32_WINNT 0x0500

/*
	Win32 impl of the console functions.
*/

namespace sani {

	namespace console {

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
		static void getBounds(ConsoleRect& bounds) {
			RECT cRect;

			GetWindowRect(GetConsoleWindow(), &cRect);

			bounds.x = cRect.left;
			bounds.y = cRect.top;
			bounds.w = cRect.right - cRect.left;
			bounds.h = cRect.bottom - cRect.top;
		}

		void open(const uint32 width, const uint32 height, const int32 x, const int32 y) {
			if (!consoleAllocated) allocateConsole();

			ShowWindow(GetConsoleWindow(), SW_SHOW);

			move(x, y);
		}
		void open(const uint32 width, const uint32 height) {
			open(height, width, 0, 0);
		}

		void move(const int32 x, const int32 y) {
			SANI_ASSERT(consoleAllocated);

			ConsoleRect rect;

			getWindowBounds(rect);

			MoveWindow(GetConsoleWindow(), x, y, static_cast<int32>(rect.w), static_cast<int32>(rect.h), true);
		}

		void resize(const uint32 width, const uint32 height) {
			SANI_ASSERT(consoleAllocated);

			ConsoleRect rect;

			getWindowBounds(rect);

			MoveWindow(GetConsoleWindow(), rect.x, rect.y, static_cast<int32>(width), static_cast<int32>(height), true);
		}
		void resizeBuffer(const uint32 columns, const uint32 rows) {
			SANI_ASSERT(consoleAllocated);

			COORD size;

			size.X = static_cast<SHORT>(columns);
			size.Y = static_cast<SHORT>(rows);

			SetConsoleScreenBufferSize(GetConsoleWindow(), size);
		}

		void hide() {
			SANI_ASSERT(consoleAllocated);

			ShowWindow(GetConsoleWindow(), SW_HIDE);
		}
		void close() {
			SANI_ASSERT(consoleAllocated);

			if (!FreeConsole()) {
				throw std::runtime_error("something went wrong while closing the console");
			}

			consoleAllocated = false;
		}
		bool isOpen() {
			return consoleAllocated;
		}

		void write(const String& str) {
			SANI_ASSERT(consoleAllocated);

			std::cout << str;
		}
		void writeLine(const String& str) {
			SANI_ASSERT(consoleAllocated);

			std::cout << str << std::endl;
		}

		void clear() {
			SANI_ASSERT(consoleAllocated);

			system("cls");
		}

		void getWindowBounds(ConsoleRect& bounds) {
			SANI_ASSERT(consoleAllocated);

			getBounds(bounds);
		}
		void getBufferBounds(uint32& columns, uint32& rows) {
			SANI_ASSERT(consoleAllocated);

			CONSOLE_SCREEN_BUFFER_INFO bufferInfo;

			GetConsoleScreenBufferInfo(GetStdHandle(STD_OUTPUT_HANDLE), &bufferInfo);

			columns = static_cast<uint32>(bufferInfo.srWindow.Right - bufferInfo.srWindow.Left + 1);
			rows = static_cast<uint32>(bufferInfo.srWindow.Bottom - bufferInfo.srWindow.Top + 1);
		}
		void getLargestBufferSize(uint32& columns, uint32& rows) {
			COORD size = GetLargestConsoleWindowSize(GetConsoleWindow());

			columns = static_cast<uint32>(size.X);
			rows = static_cast<uint32>(size.Y);
		}
	}
}
#endif