#include "sani/core/cvar/cvar_linker.hpp"
#include "sani/core/cvar/cvar_lang.hpp"
#include "sani/debug.hpp"
#include <algorithm>

namespace sani {

	CVarLinker::CVarLinker() {
	}


	CVarFile* CVarLinker::findFile(const String& fileName, std::list<CVarFile>& files) {
		auto file = std::find_if(files.begin(), files.end(), [&fileName](const CVarFile& other) {
			return fileName == other.getFilename();
		});

		if (file == files.end()) {
			pushError(SANI_ERROR_MESSAGE("could not find file with name " + fileName));

			return nullptr;
		}

		return &(*file);
	}
	void CVarLinker::linkFiles(CVarFile* file, std::list<CVarFile>& files) {
		uint32 scope = 0;

		for (uint32 i = 0; i < file->getLinesCount(); i++) {
			
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

	void CVarLinker::link(const String& fileName, std::list<CVarFile>& files) {
		CVarFile* file = findFile(fileName, files);

		if (hasErrors()) return;

		linkFiles(file, files);
	}

	CVarLinker::~CVarLinker() {
	}
}