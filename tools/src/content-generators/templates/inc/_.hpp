#include "sani/types.hpp"
#include "sani/resource/resource.hpp"
#include "sani/resource/serialization.hpp"

namespace sani {
	namespace resource {
		class $CLASSNAME : public Resource {
			public:
				$CLASSNAME();
				~$CLASSNAME();
		};
	}
}

SANI_DESERIALIZABLE_WITH(sani::resource::$UCNAMEContent, sani::resource::reader::$UCNAMEReader);