#include "sani/core/cvar/cvar_file.hpp"
#include <sstream>

namespace sani {

	CVarFile::CVarFile(const String& filename, const String& contents) : filename(filename) {
		// Split contents to lines.
		std::stringstream ss(contents);
		String line;

		// Split by new lines.
		while (std::getline(ss, line, '\n')) {
			// Remove carriage returns.
			line = line.substr(0, line.find('\r'));

			lines.push_back(line);
		}
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