#pragma once

#include "sani/resource/reader/resource_type_reader.hpp"
#include "sani/resource/serialization.hpp"

namespace sani {

	namespace resource {

		namespace reader {

			class BitmapContentReader : public ResourceTypeReader {
			public:
				~BitmapContentReader();

				String getReaderName() const { return "sani::resource::reader::BitmapContentReader"; }

				void* read(ResourceReader* reader);
			};
		}
	}
}