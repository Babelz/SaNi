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

		void getWindowBounds(ConsoleRect& rect);
		void getBufferBounds(uint32& columns, uint32 rows);
		void getLargestBufferSize(uint32& columns, uint32& rows);
#else
	#ifdef CONSOLE_HPP
		#error "Console not supported on the target platform"
	#endif
#endif
	}
}

#endif