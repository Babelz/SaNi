#ifndef CONSOLE_HPP
#define CONSOLE_HPP

#include "sani/platform/platform_config.hpp"
#include "sani/types.hpp"

namespace sani {

	/*
		TODO: write support for Linux.
	*/

	namespace console {

		/// Primitive structure containing console size
		/// and current location.
		struct ConsoleRect final {
			int32 x;
			int32 y;
			uint32 w;
			uint32 h;

			ConsoleRect() = default;

			~ConsoleRect() = default;
		};

		enum class ConsoleColor {
			Black		= 0,
			DarkBlue	= 1,
			DarkGreen	= 2,
			DarkCyan	= 3,
			DarkRed		= 4,
			DarkMagenta = 5,
			DarkYellow	= 6,
			DarkGray	= 7,
			Gray		= 8,
			Green		= 9,
			Blue		= 10,
			Cyan		= 11,
			Red			= 12,
			Magenta		= 13,
			Yellow		= 14,
			White		= 15
		};

		// Generate error if platform not valid. Console should only be used while 
		// debugging.
#if SANI_TARGET_PLATFORM == SANI_PLATFORM_WIN32 || SANI_TARGET_PLATFORM == SANI_PLATFORM_LINUX
		/// Opens the system console with given size and moves it to the given location.
		void create(const uint32 width, const uint32 height, const int32 x, const int32 y);
		/// Opens the system console with given width and height.
		void create(const uint32 width, const uint32 height);

		/// Moves the console to given location.
		void move(const int32 x, const int32 y);

		/// Resize the window.
		void resizeWindow(const uint32 width, const uint32 height);
		/// Resize the text buffer.
		void resizeBuffer(const uint32 columns, const uint32 rows);

		/// Hides the system console.
		void hide();
		/// Hides and disposes the system console.
		void close();
		
		/// Returns true if this process contains an console.
		bool created();
		/// Returns boolean representing the visibility of the console.
		bool visible();

		/// Shows the console.
		void show();

		/// Writes given string to the console.
		void write(const String& str);
		/// Writes new line to the console.
		void writeLine(const String& str);

		/// Clears the console.
		void clear();

		/// Gets the console window bounds.
		void windowBounds(ConsoleRect& rect);
		/// Gets the window text buffer bounds.
		void bufferBounds(uint32& columns, uint32 rows);
		/// Returns the max size of the console text buffer.
		void largestBufferSize(uint32& columns, uint32& rows);

		void resetColor();
		void textColor(const ConsoleColor color);
#else
	#ifdef CONSOLE_HPP
		#error "Console not supported on the target platform"
	#endif
#endif
	}
}

#endif