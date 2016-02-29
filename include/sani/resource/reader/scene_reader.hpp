#pragma once

#include "sani/resource/reader/resource_type_reader.hpp"
#include "sani/rtti/Reflectable.hpp"
#include "sani/preprocessor/rtti_runtime.hpp"

namespace sani {

	namespace resource {

		namespace reader {

			class SceneReader : public ResourceTypeReader {
				DECLARE_REFLECTABLE;
			public:
				~SceneReader();

				String getReaderName() const { return "sani::resource::reader::SceneReader"; }

				void* read(ResourceReader* reader);
			};
		}
	}
}