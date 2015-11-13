#include "sani/platform/file/file_system.hpp"
#include "sani/resource/$LCNAME_content.hpp"
#include "sani/resource/pipeline/$LCNAME_importer.hpp"

namespace sani {
	namespace resource {
		namespace pipeline {

			$CLASSNAME::$CLASSNAME() 
				: ContentImporter() {

			}

			$CLASSNAME::~$CLASSNAME() { }

			ResourceItem* $CLASSNAME::import(const String& filename, io::FileSystem* fileSystem) const {
				return nullptr;
			}
		}
	}
}