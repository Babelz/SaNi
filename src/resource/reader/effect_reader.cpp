#include "sani/resource/reader/effect_reader.hpp"
#include "sani/resource/reader/resource_reader.hpp"
#include "sani/platform/graphics/graphics_device.hpp"
#include "sani/resource/effect.hpp"

namespace sani {

	namespace resource {

		namespace reader {

			namespace {
				auto &db = sani::rtti::TypeDatabase::getInstance();

				struct ReflectionInjector {
					ReflectionInjector() {
						RTTI_REGISTER_TYPE(ResourceTypeReader);
						RTTI_REGISTER_TYPE(EffectReader);
						RTTI_DECLARE_BASECLASSES(EffectReader, typeof(ResourceTypeReader));
						RTTI_DEFAULT_DYNAMIC_CTOR(EffectReader);
					}
				};

				static ReflectionInjector ignoreme;
			}

			EffectReader::~EffectReader() {
			}

			void* EffectReader::read(ResourceReader* reader) {
				// lets try this
				const uint8 compiled = reader->readByte();

				// if its compiled 
				// 1) we need to be sure to have extension supported
				// 2) we just need to read the compiled data
				if (compiled) {
					String binary = reader->readString();
					// glProgramnBinaryETC shit..
					throw std::logic_error("Not implemented");
				}
				// fallback scheme
				// we dont have the extension OR the effect isnt compiled
				
				// first is vertex shader
				String vertexCode = reader->readString();
				// then fragment
				String fragmentCode = reader->readString();

				// compile shaders
				GraphicsDevice* device = reader->getGraphicsDevice();
				Effect* effect = new Effect(device, vertexCode, fragmentCode);

				return effect;
			}
		}
	}
}