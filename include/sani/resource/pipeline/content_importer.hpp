#pragma once

#include "sani/types.hpp"
#include "sani/platform/file/file_system.hpp"
#include "sani/forward_declare.hpp"
SANI_FORWARD_DECLARE_2(sani, resource, ResourceItem);

namespace sani {

	namespace resource {

		namespace pipeline {
			class ContentImporter  {
			public:
				ContentImporter() = default;
				virtual ~ContentImporter() = default;
				virtual ResourceItem* import(const String& filename, io::FileSystem* fileSystem) const = 0;
			};
		}
	}
}