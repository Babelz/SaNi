#pragma once

#include "sani/resource/compiler/resource_type_writer.hpp"

namespace sani {
	namespace resource {
		namespace compiler {
			// TODO add all primitives
			class Uint8Writer : public ResourceTypeWriter {
			public:
				void write(ResourceWriter* writer, void* value);
			};
		}
	}
}