#pragma once

#include "sani/types.hpp"
#include "sani/forward_declare.hpp"
#include "sani/rtti/reflectable.hpp"
#include "sani/preprocessor/rtti.hpp"
#include "sani/preprocessor/rtti_runtime.hpp"

SANI_FORWARD_DECLARE_3(sani, resource, reader, ResourceReader);
SANI_FORWARD_DECLARE_3(sani, resource, reader, ResourceTypeReaderManager);

namespace sani {

	namespace resource {

		namespace reader {

			/// Reads specified resource
			///
			/// @author siquel
			class ResourceTypeReader {
				DECLARE_REFLECTABLE;
			public:
				/// Default constructor
				ResourceTypeReader() = default;
				/// Default destructor
				virtual ~ResourceTypeReader() = default;
				/// Namespace prefixed reader name
				virtual String getReaderName() const = 0;

				/// Initializes the type reader and adds itself to manager
				/// (not used for prebuilt readers)
				virtual void initialize(ResourceTypeReaderManager* manager) { }
				/// Reads the data type
				/// @param reader The content reader which has the stream to read
				virtual void* read(ResourceReader* reader) = 0;
			};
		}
	}
}