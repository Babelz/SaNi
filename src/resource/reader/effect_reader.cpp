#include "sani/resource/reader/effect_reader.hpp"
#include "sani/resource/reader/resource_reader.hpp"
#include "sani/platform/graphics/graphics_device.hpp"

namespace sani {
	namespace resource {
		namespace reader {
			EffectReader::~EffectReader() {}

			void* EffectReader::read(ResourceReader* reader) {
				// lets try this
				uint8 compiled = reader->readByte();

				// if its compiled 
				// 1) we need to be sure to have extension supported
				// 2) we just need to read the compiled data
				// TODO
				if (compiled) {
					// TODO replace this with non-null terminated
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
				// TODO if thers more?

				// compile shaders
				GraphicsDevice* device = reader->getGraphicsDevice();
				uint32 vertex, fragment, program;

				// TODO error check or soemthing?
				device->compileShader(vertex, vertexCode.c_str(), ShaderType::Vertex);
				device->compileShader(fragment, fragmentCode.c_str(), ShaderType::Vertex);

				device->createProgram(program);
				device->linkToProgram(program, vertex, true);
				device->linkToProgram(program, fragment, true);
				device->linkProgram(program);

				return nullptr;
			}
		}
	}
}