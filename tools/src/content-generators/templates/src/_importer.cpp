#include "sani/platform/file/file_system.hpp"
#include "sani/platform/$LCNAME_content.hpp"
#include "sani/platform/$LCNAME_importer.hpp"

namespace sani {
	namespace resource {
		namespace pipeline {

			$CLASSNAME::$CLASSNAME() 
				: ContentImporter() {

			}

			$CLASSNAME::~$CLASSNAME() { }

			ResourceItem* $CLASSNAME::import(const String& filename, FileSystem* fileSystem) const {
				return nullptr;
			}
		}
	}
}