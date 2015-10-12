#pragma once
#include "../file_stream.hpp"
namespace sani {
	namespace io {
		inline Filemode FileStream::getOpenMode() const {
			return mode;
		}

		inline const String& FileStream::getPath() const {
			return filePath;
		}
	}
}