#include "sani/resource/compiler/resource_writer.hpp"
#include "sani/resource/$LCNAME_content.hpp"
#include "sani/resource/compiler/$LCNAME_writer.hpp"
#include "sani/resource/serialization.hpp"

namespace sani {
	namespace resource {
		namespace compiler {

			$CLASSNAME::$CLASSNAME() 
				: ResourceTypeWriter() {

			}

			$CLASSNAME::~$CLASSNAME() { }

			String $CLASSNAME::getRuntimeReader() const {
				return DeserializableWith<$UCNAMEContent>::value();
			}

			void $CLASSNAME::write(ResourceWriter* writer, const void* value) {
				
			}
		}
	}
}