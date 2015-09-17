#include "sani/core/cvar/cvar_file.hpp"

namespace sani {

	CVarFile::CVarFile(const String& filename, const String& contents) : filename(filename) {
		// TODO: parse lines from raw.
	}

	const String& CVarFile::getFilename() const {
		return filename;
	}
	const size_t CVarFile::getLinesCount() const {
		return lines.size();
	}

	const String& CVarFile::lineAtIndex(const size_t index) const {
		return lines[index];
	}
	
	void CVarFile::removeLineAtIndex(const size_t index) {
		lines.erase(lines.begin() + index);
	}
	void CVarFile::insertLines(const size_t index, const std::vector<String>& lines) {
		for (size_t i = 0; i < lines.size(); i++) {
			this->lines.insert(this->lines.begin() + index + i, lines[i]);
		}
	}

	CVarFile::~CVarFile() {
	}
}