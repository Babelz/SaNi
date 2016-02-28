#pragma once

#include "sani/resource/reader/resource_type_reader.hpp"

namespace sani {

	namespace resource {

		namespace reader {

			class SceneReader : public ResourceTypeReader {
			public:
				~SceneReader();

				String getReaderName() const { return "sani::resource::reader::SceneReader"; }

				void* read(ResourceReader* reader);
			};
		}
	}
}