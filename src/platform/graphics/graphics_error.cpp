#include "sani/platform/graphics/graphics_error.hpp"

namespace sani {
	namespace graphics {

		// WinGL/Android implementations of the graphics error.
#if SANI_TARGET_PLATFORM == SANI_PLATFORM_WIN32 || SANI_TARGET_PLATFORM == SANI_PLATFORM_ANDROID
		GraphicsError::GraphicsError(const GLuint apiErrorCode, const String& function, const int32 lineNumber) : function(function),
																												  lineNumber(lineNumber) {
			this->apiErrorCode = static_cast<int32>(apiErrorCode);

			translate(this->apiErrorCode);
		}
		GraphicsError::GraphicsError(const String& message, const String& function, const int32 lineNumber) : message(message),
																											  function(function),
																											  lineNumber(lineNumber),
																											  apiErrorCode(1282) {		// Just mark custom errors with GL invalid operation.
		}

		const String& GraphicsError::getMessage() const {
			return message;
		}
		const String& GraphicsError::getFunctionName() const {
			return function;
		}

		int32 GraphicsError::getLineNumber() const {
			return lineNumber;
		}
		int32 GraphicsError::getAPIErrorCode() const {
			return apiErrorCode;
		}

		void GraphicsError::translate(const int32 apiErrorCode) {
			// Translate error codes to strings.
			// Messages are being copied from link found under.
			// https://www.opengl.org/sdk/docs/man/docbook4/xhtml/glGetError.xml

			switch (apiErrorCode) {
			case GL_INVALID_ENUM:
				message = "An unacceptable value was specified for an enumerated argument";
				break;
			case GL_INVALID_VALUE:
				message = "A numeric argument was out of range";
				break;
			case GL_INVALID_OPERATION:
				message = "The specified operation was not allowed in the current state";
				break;
			case GL_INVALID_FRAMEBUFFER_OPERATION:
				message = "The framebuffer object was not complete";
				break;
			case GL_OUT_OF_MEMORY:
				message = "There was not enough memory left to execute the given command";
				break;

#if SANI_TARGET_PLATFORM != SANI_PLATFORM_ANDROID	// Android does not support these errors.
			case GL_STACK_UNDERFLOW:
				message = "An attempt was made to perform an operation that would cause an internal stack to underflow";
				break;
			case GL_STACK_OVERFLOW:
				message = "An attempt was made to perform an operation that would cause an internal stack to overflow";
				break;
#endif

			default:
				throw std::logic_error("Invalid OpenGL error code");
			}
		}
#endif
	}
}