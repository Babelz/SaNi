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
	CVarFile::CVarFile() {
	}

	const String& CVarFile::getFilename() const {
		return filename;
	}
	const uint32 CVarFile::getLinesCount() const {
		return lines.size();
	}
	const String& CVarFile::lineAtIndex(const size_t index) const {
		return lines[index];
	}
	String& CVarFile::lineAtIndex(const size_t index) {
		return lines[index];
	}
	void CVarFile::overwriteLineAtIndex(const size_t index, const String& newLine) {
		lines[index] = newLine;
	}
	
	void CVarFile::removeLineAtIndex(const size_t index) {
		lines.erase(lines.begin() + index);
	}

	CVarFile::~CVarFile() {
	}
}