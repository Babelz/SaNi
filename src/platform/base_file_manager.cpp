#include "sani/platform/base_file_manager.hpp"
#include "sani/platform/file.hpp"

namespace sani {
	namespace io {

		BaseFileManager::BaseFileManager()  {

		}

		BaseFileManager::~BaseFileManager() {
			
		}

		bool BaseFileManager::isAbsolutePath(const String& path) const {
			// Most platforms are running linux, so we overwrite this in win32
			return !path.empty() && path.at(0) == '/';
		}

	}
}