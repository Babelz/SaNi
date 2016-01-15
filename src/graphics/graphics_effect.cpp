#include "sani/graphics/graphics_effect.hpp"

namespace sani {

	namespace graphics {

		/*
			Uniform class impl.
		*/

		EffectUniform::EffectUniform(const UniformType type, const uint32 location, const String& name) : type(type),
																				  location(location), 
																				  name(name){
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

		/*
			Effect class impl.
		*/

		GraphicsEffect::GraphicsEffect(GraphicsDevice* const device, const uint32 effect) : device(device),
																							effect(effect) {
		}

		void GraphicsEffect::locateEffectUniforms() {
			const int32 total = -1;

		}
		
		uint32 GraphicsEffect::getEffectID() const {
		}

		void GraphicsEffect::listUniforms(UniformList& uniforms) {
		}

		GraphicsEffect::~GraphicsEffect() {
		}
	}
}