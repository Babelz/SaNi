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
				throw std::logic_error("unsupported or invalid value type");
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
				throw std::logic_error("unsupported or invalid shader type");
			}
		}

		inline GLuint SaNiBufferToAPIBuffer(const BufferType type) {
			switch (type) {
			case ElementArrayBuffer:
				return GL_ELEMENT_ARRAY_BUFFER;
			case ArrayBuffer:
				return GL_ARRAY_BUFFER;
			default:
				throw std::logic_error("unsupported or invalid buffer type");
			}
		}

		inline GLenum SaNiUsageToAPIUsage(const BufferUsage usage) {
			switch (usage) {
			case Static:
				return GL_STATIC_DRAW;
			case Dynamic:
				return GL_DYNAMIC_DRAW;
			default:
				throw std::logic_error("unsupported or invalid buffer usage");
			}
		}
	}
}