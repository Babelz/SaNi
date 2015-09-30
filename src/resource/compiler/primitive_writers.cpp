#include "sani/resource/compiler/primitive_writers.hpp"
#include "sani/resource/compiler/resource_writer.hpp"
namespace sani {
	namespace resource {
		namespace compiler {
			void Uint8Writer::write(ResourceWriter* writer, void* value) {
				uint8* ptr = static_cast<uint8*>(value);
				writer->write(*ptr);
			}
		}
	}
}