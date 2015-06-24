#include "sani/platform/file.hpp"

namespace sani {
	namespace io {
		
		File::File(const String& path) : path(path) {

		}

		File::~File() {

		}

		const String& File::getPath() const {
			return path;
		}

	}
}



