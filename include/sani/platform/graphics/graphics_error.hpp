#include "sani/platform/graphics/graphics_precompiled.hpp"
#include "sani/platform/platform_config.hpp"
#include "sani/types.hpp"

namespace sani {
	namespace graphics {
		
		// Creates new instance of the graphics error by translating the 
		// API error code to custom message.
		#define GRAPHICS_ERROR(apiErrorCode) GraphicsError(apiErrorCode, __FUNCTION__, __LINE__)

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

#if SANI_TARGET_PLATFORM == SANI_PLATFORM_WIN32 || SANI_TARGET_PLATFORM == SANI_PLATFORM_ANDROID
			// TODO: implement API checking 
			//       for WinGL and WinDX.

			GraphicsError(const GLuint apiErrorCode, const String& function, const int32 lineNumber);
			/// Creates new instance of the GraphicsError object with a custom error message.
			GraphicsError(const String& message, const String& function, const int32 lineNumber);
#endif

			const String& getMessage() const;
			const String& getFunctionName() const;

			int32 getLineNumber() const;
			int32 getAPIErrorCode() const;
		};
	}
}