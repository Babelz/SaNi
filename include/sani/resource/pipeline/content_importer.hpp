#pragma once

#include "sani/types.hpp"
#include "sani/platform/file/file_system.hpp"

namespace sani {

	namespace resource {

		namespace pipeline {

			template <class ContentType, class Implementer>
			class ContentImporter  {
			public:
				ContentImporter();
				ContentType* import(const String& filename, io::FileSystem* fileSystem) const;
			private:
				const Implementer impl;
			};
		}
	}
}

namespace sani {
	namespace resource {
		namespace pipeline {

			
			template <class T, class U>
			ContentImporter<T, U>::ContentImporter() {}

			template <class T, class U>
			T* ContentImporter<T, U>::import(const String& filename, io::FileSystem* fileSystem) const {
				return impl.import(filename, fileSystem);
			}
		}
	}
}