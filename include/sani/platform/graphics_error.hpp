#include "sani/platform/graphics_precompiled.hpp"
#include "sani/platform/platform_config.hpp"
#include "sani/precompiled.hpp"

namespace sani {
	namespace graphics {
		
		/// @class GraphicsError "sani/platform/graphics_error.hpp"
		///
		/// Represents a generic graphics error used by the graphics apis.
		class GraphicsError {
		private:
			int32 lineNumber;
			int32 apiErrorCode;

			String message;
			String function;

			/*
				API specific translation method used to translate 
				API errors to "SaNi graphics errors"
			*/

			void translate(const int32 apiErrorCode);
		public:

#if SANI_TARGET_PLATFORM == SANI_PLATFORM_WIN32
			// TODO: implement API checking 
			//       for WinGL and WinDX.

			/// WinGL constructor.
			GraphicsError(const GLuint apiErrorCode, const String& function, const int32 lineNumber);
#endif

			const String& getMessage() const;
			const String& getFunctionName() const;
			int32 getLineNumber() const;
		};
	}
}