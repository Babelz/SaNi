#include "sani/platform/graphics/graphics_device.hpp"
#include "sani/graphics/graphics_effect.hpp"

namespace sani {

	namespace graphics {

		/*
			Uniform class impl.
		*/

		EffectUniform::EffectUniform(GraphicsDevice* const device, const uint32 effect, const UniformType type, const uint32 location, const String& name) 
			: effect(effect), device(device), type(type), location(location), name(name) {
		}

		UniformType EffectUniform::getType() const {
			return type;
		}
		const String& EffectUniform::getName() const {
			return name;
		}
		uint32 EffectUniform::getLocation() const {
			return location;
		}
		void EffectUniform::setData(void* data) {
			device->setShaderUniform(effect, name.c_str(), data, type);
		}

		/*
			Effect class impl.
		*/

		GraphicsEffect::GraphicsEffect(GraphicsDevice* const device, const uint32 effect) : device(device),
																							effect(effect) {
		}

		void GraphicsEffect::locateEffectUniforms() {
			int32 count = device->getUniformsCount(effect);

			for (int32 i = 0; i < count; i++) {
				String	name;
				int32	location;
				uint32	type;
				int32	valuesCount;

				device->getUniformInformation(effect, i, location, name, type, valuesCount);
				
				uniforms.push_back(EffectUniform(device, effect, static_cast<UniformType>(type), location, name));
			}
		}
		
		uint32 GraphicsEffect::getEffect() const {
			return effect;
		}

		void GraphicsEffect::listUniforms(UniformList& uniforms) const {
			uniforms = this->uniforms;
		}

		GraphicsEffect::~GraphicsEffect() {
			device->useProgram(0);
			device->deleteShader(effect);
		}
	}
}