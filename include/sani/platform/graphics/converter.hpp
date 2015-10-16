#pragma once

#include "sani/platform/platform_config.hpp"
#include "graphics_precompiled.hpp"

namespace sani {
	namespace graphics {
		
		/*
			TODO: add platform wrappers.
		*/

		inline GLenum SaNiTypeToAPIType(const Type type) {
			switch (type) {
			case UByte:
				return GL_UNSIGNED_BYTE;
			case UShort:
				return GL_UNSIGNED_SHORT;
			case UInt:
				return GL_UNSIGNED_INT;
			case Float:
				return GL_FLOAT;
			default:
				return GL_UNSIGNED_BYTE;
			}
		}

		inline GLboolean SaNiBoolToAPIBool(const bool value) {
			return static_cast<GLboolean>(value);
		}

		inline GLuint SaNiShaderToAPIShader(const ShaderType type) {
			switch (type) {
			case Vertex:
				return GL_VERTEX_SHADER;
			case Pixel:
				return GL_FRAGMENT_SHADER;
			default:
				return GL_VERTEX_SHADER;
			}
		}
	}
}