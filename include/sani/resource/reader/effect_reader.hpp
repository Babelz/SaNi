#pragma once

#include "sani/resource/reader/resource_type_reader.hpp"

namespace sani {
	namespace resource {
		namespace reader {
			/// Class that reads shaders
			///
			/// @author siquel
			class EffectReader : public ResourceTypeReader {
			public:
				~EffectReader();
				String getReaderName() const { return "sani::resource::reader::EffectReader"; }

				void* read(ResourceReader* reader);
			};
		}
	}
}