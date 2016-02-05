#include "sani/resource/effect.hpp"
#include "sani/platform/graphics/graphics_device.hpp"

namespace sani {

	namespace resource {

		Effect::Effect(graphics::GraphicsDevice* device, const String& vcode, const String& fcode) {
			uint32 vertex, fragment;

			device->compileShader(vertex, vcode.c_str(), graphics::ShaderType::Vertex);
			device->compileShader(fragment, fcode.c_str(), graphics::ShaderType::Vertex);

			device->createProgram(id);
			device->linkToProgram(id, vertex, true);
			device->linkToProgram(id, fragment, true);
			device->linkProgram(id);
		}

		uint32 Effect::getProgram() const {
			return id;
		}
	}
}