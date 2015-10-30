#pragma once
#include "sani/resource/compiler/resource_type_writer.hpp"
#include "sani/resource/texture2d.hpp"
namespace sani {
	namespace resource {
		namespace compiler {
			class Texture2DWriter : public ResourceTypeWriter {
			public:
				void write(ResourceWriter* writer, void* value) override;
			};
		}
	}
}