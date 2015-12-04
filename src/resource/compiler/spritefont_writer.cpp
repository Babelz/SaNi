#include "sani/resource/compiler/resource_writer.hpp"
#include "sani/resource/spritefont_content.hpp"
#include "sani/resource/compiler/spritefont_writer.hpp"
#include "sani/resource/serialization.hpp"

namespace sani {
	namespace resource {
		namespace compiler {

			SpriteFontWriter::SpriteFontWriter() 
				: ResourceTypeWriter() {

			}

			SpriteFontWriter::~SpriteFontWriter() { }

			String SpriteFontWriter::getRuntimeReader() const {
				return DeserializableWith<SpriteFontContent>::value();
			}

			void SpriteFontWriter::write(ResourceWriter* writer, const void* value) {
				
			}
		}
	}
}