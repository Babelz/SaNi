#include "sani/core/utils/string_utils.hpp"
#include "sani/core/cvar/cvar_linker.hpp"
#include "sani/core/cvar/cvar_lang.hpp"
#include "sani/debug.hpp"
#include <algorithm>

namespace sani {

	CVarLinker::CVarLinker() {
	}


	CVarFile* CVarLinker::findFile(const String& filename, std::list<CVarFile>& files) {
		auto file = std::find_if(files.begin(), files.end(), [&filename](const CVarFile& other) {
			return filename == other.getFilename();
		});

		if (file == files.end()) {
			pushError(SANI_ERROR_MESSAGE("could not find file with name " + filename));

			return nullptr;
		}

		return &(*file);
	}
	void CVarLinker::linkFiles(CVarFile* file, std::list<CVarFile>& files) {
		scope = 0;

		for (uint32 i = 0; i < file->getLinesCount(); i++) {
			String line = file->lineAtIndex(i);

			if (cvarlang::lang::containsComment(line)) line = line.substr(0, line.find("//"));
			utils::trim(line);

			if (cvarlang::lang::startsWithRequire(line)) {
				updateScope(line);
			} else if (cvarlang::lang::startsWithInclude(line)) {
				linkFile(file, line, files);
				copyContents(file, i, line, files);
			}
		}
	}

	void CVarLinker::copyContents(CVarFile* file, const uint32 lineIndex, const String& line, std::list<CVarFile>& files) {
		if (hasErrors()) return;

		CVarFile* other = findFile(line, files);

		// "Link"
		file->removeLineAtIndex(lineIndex);
		rootRecord->links.push_back(other);
	}
	void CVarLinker::linkFile(CVarFile* file, String& line, std::list<CVarFile>& files) {
		// Begin by looking if the file we are linking needs to be linked.

		// Require that the scope is 0.
		if (scope != 0) {
			pushError(SANI_ERROR_MESSAGE("link error, can't include files inside require statements"));

			return;
		}

		line = line.substr(cvarlang::lang::IncludeKeyword.size() + 1);

		CVarFile* other = findFile(line, files);

		// Check wether the file we want to link exists.
		if (other == nullptr) {
			pushError(SANI_ERROR_MESSAGE("could not find file with name " + line));
			
			return;
		}

		// Link other files with this one.
		linkFiles(other, files);
		rootRecord->links.push_back(other);
	}

	void CVarLinker::updateScope(const String& line) {
		if (hasErrors()) return;

		if (line.size() == cvarlang::lang::RequireKeyword.size()) {
			scope--;
		} else {
			scope++;
		}
	}

	void CVarLinker::pushError(const String& message) {
		errorBuffer.push(message);
	}

	bool CVarLinker::hasErrors() const {
		return !errorBuffer.empty();
	}
	String CVarLinker::getNextError() {
		String message = errorBuffer.top();
		errorBuffer.pop();

		return message;
	}

	void CVarLinker::link(const String& filename, std::list<CVarFile>& files, LinkRecord& linkRecord) {
		CVarFile* file = findFile(filename, files);

		if (hasErrors()) return;

		rootRecord = &linkRecord;
		rootRecord->file = file;

		linkFiles(file, files);
	}

	CVarLinker::~CVarLinker() {
	}
}