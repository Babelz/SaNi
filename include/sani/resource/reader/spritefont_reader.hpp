#pragma once
#include "sani/resource/reader/resource_type_reader.hpp"

namespace sani {
	namespace resource {
		namespace reader {
			class SpriteFontReader : public ResourceTypeReader {
			public:
				SpriteFontReader();
				~SpriteFontReader();
				String getReaderName() const { return "sani::resource::reader::SpriteFontReader"; }
				void* read(ResourceReader* reader) override;
			};
		}
	}
}