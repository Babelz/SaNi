#include "sani/core/cvar/cvar_linker.hpp"
#include "sani/core/cvar/link_record.hpp"
#include "sani/core/cvar/cvar_file.hpp"
#include "sani/core/cvar/cvar_lang.hpp"
#include <regex>

namespace sani {

	CVarLinker::CVarLinker() {
	}

	void CVarLinker::pushError(const String& error) {
		errorBuffer.push(error);
	}

	bool CVarLinker::hasErrors() const {
		return errorBuffer.size() != 0;
	}
	String CVarLinker::getNextError() {
		const String error = errorBuffer.top();
		errorBuffer.pop();

		return error;
	}

	void CVarLinker::link(std::list<CVarFile>& files) {
		std::list<LinkRecord> records;

		// Process each file.
		for (CVarFile& file : files) {
			// Process each line.
			for (size_t i = 0; i < file.getLinesCount(); i++) {
				// 1) Check for include keyword.
				// 2) Check that r.match.len == line.len
				//		if not, push error, return
				//		else link, continue

				String line = file.lineAtIndex(i);
				
				// Check for includes.
			}
		}
	}
	
	CVarLinker::~CVarLinker() {
	}
}