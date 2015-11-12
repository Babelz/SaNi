#pragma once

#include "sani/resource/reader/resource_type_reader.hpp"

namespace sani {
	namespace resource {
		namespace reader {
			class $CLASSNAME : public ResourceTypeReader {
			public:
				$CLASSNAME();
				~$CLASSNAME();
				String getReaderName() const { return "sani::resource::reader::$CLASSNAME"; }
				void* read(ResourceReader* reader) override;
			};
		}
	}
}