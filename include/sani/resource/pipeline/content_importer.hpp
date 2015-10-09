#pragma once

#include "sani/types.hpp"
#include "sani/platform/file/file_system.hpp"

namespace sani {

	namespace resource {

		namespace pipeline {

			template <typename ContentType, class Implementer>
			class ContentImporter {
			public:
				ContentImporter() = default;
				~ContentImporter() = default;
				ContentType* import(const String& filename, io::FileSystem* fileSystem) const {
					return impl.import(filename, fileSystem);
				}
			private:
				Implementer impl;
			};
		}
	}
}