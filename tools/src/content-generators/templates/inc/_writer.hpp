#pragma once
#include "sani/resource/compiler/resource_type_writer.hpp"

namespace sani {
	namespace resource {
		namespace compiler {
			class $CLASSNAME : public ResourceTypeWriter {
				public:
					$CLASSNAME();
					~$CLASSNAME();
					void write(ResourceWriter* writer, const void* value) override;
					String getRuntimeReader() const override;
			};
		}
	}
}