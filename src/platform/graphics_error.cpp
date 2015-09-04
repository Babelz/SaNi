#include "sani/platform/graphics_error.hpp"

namespace sani {
	namespace graphics {

		// WinGL implementations of the graphics error.
#if SANI_TARGET_PLATFORM == SANI_PLATFORM_WIN32
		GraphicsError::GraphicsError(const GLuint apiErrorCode, const String& function, const int32 lineNumber) : function(function),
																												  lineNumber(lineNumber) {
			this->apiErrorCode = static_cast<int32>(apiErrorCode);

			translate(this->apiErrorCode);
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
			case GL_STACK_UNDERFLOW:
				message = "An attempt was made to perform an operation that would cause an internal stack to underflow";
				break;
			case GL_STACK_OVERFLOW:
				message = "An attempt was made to perform an operation that would cause an internal stack to overflow";
				break;
			default:
				throw std::logic_error("Invalid OpenGL error code");
			}
		}
#endif
	}
}