#include "sani/core/logging/log.hpp"
#include "sani/platform/graphics/graphics_device.hpp"
#include "sani/graphics/graphics_effect.hpp"
#include "sani/debug.hpp"

#include <algorithm>
#include <sstream>

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
			device->bindEffect(effect);

			device->setUniformValue(name, data, type);
		
			device->bindEffect(NULL);
		}

		/*
			Effect class impl.
		*/

		GraphicsEffect::GraphicsEffect(GraphicsDevice* const device, const uint32 effect) : device(device),
																							effect(effect) {
			SANI_ASSERT(device != nullptr);

			locateEffectUniforms();
		}
		GraphicsEffect::GraphicsEffect(GraphicsEffect& other) : device(other.device),
															    effect(other.effect), 
																uniforms(other.uniforms) {
		}
		GraphicsEffect::GraphicsEffect() : device(nullptr),
										   effect(0) {
		}

		void GraphicsEffect::locateEffectUniforms() {
			device->bindEffect(effect);

			const int32 count = device->getUniformsCount();

			for (int32 i = 0; i < count; i++) {
				String	name;
				uint32	location;
				uint32	type;
				int32	valuesCount;

				device->getUniformInformation(i, location, name, type, valuesCount);

				uniforms.push_back(EffectUniform(device, effect, static_cast<UniformType>(type), location, name));
			}

			device->bindEffect(NULL);
		}
		
		uint32 GraphicsEffect::getEffect() const {
			return effect;
		}
		
		void GraphicsEffect::listUniforms(UniformList& uniforms) const {
			uniforms = this->uniforms;
		}
		bool GraphicsEffect::containsUniform(const String& name) const {
			return std::find_if(uniforms.begin(), uniforms.end(), [&name](const EffectUniform& uniform) {
				return uniform.getName() == name;
			}) != uniforms.end();
		}
		EffectUniform* const GraphicsEffect::findUniform(const String& name){
			for (EffectUniform& uniform : uniforms) {
				if (uniform.getName() == name) return &uniform;
			}

			// Not found, return null.
			return nullptr;
		}

		void GraphicsEffect::bind() {
			if (device == nullptr) return;

			device->bindEffect(effect);
		}
		void GraphicsEffect::unbind() {
			if (device == nullptr) return;

			device->bindEffect(NULL);
		}

		GraphicsEffect::~GraphicsEffect() {
		}

		GraphicsEffect GraphicsEffect::compile(GraphicsDevice* const device, const String& vertexSource, const String& fragmentSource) {
			SANI_ASSERT(device != nullptr);

			String errors;
			const auto effect = device->compileEffect(vertexSource.c_str(), fragmentSource.c_str(), errors);

			if (!errors.empty()) {
				std::stringstream ss;
				ss << "errors occurred while compiling effect, message: ";
				ss << errors;

				FNCLOG_ERR(log::OutFlags::All, ss.str());
			}

			return GraphicsEffect(device, effect);
		}

		GraphicsEffect& GraphicsEffect::operator =(const GraphicsEffect& other) {
			this->device = other.device;
			this->effect = other.effect;
			this->uniforms = other.uniforms;

			return *this;
		}
	}
}