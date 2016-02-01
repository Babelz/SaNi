#pragma once

#include "sani/resource/reader/resource_reader.hpp"

namespace sani {

	namespace resource {

		namespace reader {

			template <class ObjectType>
			ObjectType* ResourceReader::readObject() {
				uint32 index = static_cast<uint32>(read7BitEncodedInt());

				SANI_ASSERT(index < readers.size());

				ResourceTypeReader* reader = readers[index];

				return static_cast<ObjectType*>(reader->read(this));
			}
		}
	}
}