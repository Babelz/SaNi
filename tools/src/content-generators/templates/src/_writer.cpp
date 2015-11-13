#include "sani/resource/compiler/resource_writer.hpp"
#include "sani/resource/$LCNAME_content.hpp"
#include "sani/resource/compiler/$LCNAME.hpp"
#include "sani/serialization.hpp"
namespace sani {
	namespace resource {
		namespace compiler {

			$CLASSNAME::$CLASSNAME() 
				: ResourceTypeWriter() {

			}

			$CLASSNAME::~$CLASSNAME() { }

			String $CLASSNAME::getRuntimeReader() const {
				return DeserializableWith<$LCNAMEContent>::value();
			}

			void $CLASSNAME::write(ResourceWriter* writer, const void* value) {
				
			}
		}
	}
}