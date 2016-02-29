#pragma once

#include "sani/resource/reader/resource_type_reader.hpp"

namespace sani {

	namespace resource {

		namespace reader {

			/// Reads 2D texture content
			/// 
			/// @author siquel
			class Texture2DReader : public ResourceTypeReader {
				DECLARE_REFLECTABLE;
			public:
				~Texture2DReader();
				String getReaderName() const { return "sani::resource::reader::Texture2DReader"; }

				void* read(ResourceReader* reader);
			};
		}
	}
}