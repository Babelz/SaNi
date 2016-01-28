#include "sani/platform/graphics/graphics_device.hpp"
#include "sani/graphics/graphics_effect.hpp"
#include "sani/debug.hpp"
#include <algorithm>

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
			const int32 count = device->getUniformsCount(effect);

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

			device->useProgram(effect);
		}
		void GraphicsEffect::unbind() {
			if (device == nullptr) return;

			device->useProgram(0);
		}

		GraphicsEffect::~GraphicsEffect() {
		}

		GraphicsEffect GraphicsEffect::compile(GraphicsDevice* const device, const String& vertexSource, const String& fragmentSource) {
			uint32 vertex	= 0;
			uint32 fragment = 0;
			uint32 effect	= 0;

			device->compileShader(vertex, vertexSource.c_str(), ShaderType::Vertex);
			SANI_ASSERT(!device->hasErrors());
			
			device->compileShader(fragment, fragmentSource.c_str(), ShaderType::Fragment);
			SANI_ASSERT(!device->hasErrors());

			device->createProgram(effect);
			device->linkToProgram(effect, vertex, true);
			device->linkToProgram(effect, fragment, true);
			device->linkProgram(effect);
			SANI_ASSERT(!device->hasErrors());

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