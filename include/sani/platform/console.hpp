#ifndef CONSOLE_HPP
#define CONSOLE_HPP

#include "sani/platform/platform_config.hpp"
#include "sani/types.hpp"

namespace sani {

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

		void resize(const uint32 width, const uint32 height);
		void resizeBuffer(const uint32 columns, const uint32 rows);

		/// Hides the system console.
		void hide();
		/// Hides and disposes the system console.
		void close();
		
		bool created();
		bool visible();

		void show();

		void write(const String& str);
		void writeLine(const String& str);

		void clear();

		void windowBounds(ConsoleRect& rect);
		void bufferBounds(uint32& columns, uint32 rows);
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