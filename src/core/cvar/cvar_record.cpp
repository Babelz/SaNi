#include "sani/core/utils/string_utils.hpp"
#include "sani/core/cvar/cvar_record.hpp"
#include "sani/core/cvar/cvar_lang.hpp"
#include <sstream>
#include <iostream>

namespace sani {

	CVarRecord::CVarRecord(const CVarToken& token, const CVar& cvar) :  token(token),
																		cvar(cvar) {
		// No need to check if volatile, the compiler should do this check.
		const String line = token.getLine();
		const int32 spos = utils::position(line, " ", 2);

		if (spos != line.npos) {
			originalValue = line.substr(spos + 1, line.size() - spos);
			indexOfValue = spos + 1;

			// Remove comments, trim.
			if (cvarlang::lang::containsComment(originalValue)) originalValue = originalValue.substr(0, originalValue.find("//"));

			utils::trim(originalValue);
		}
	}

	uint32 CVarRecord::getLineNumber() const {
		return token.getLineNumber();
	}
	const String& CVarRecord::getFilename() const {
		return token.getFilename();
	}

	String CVarRecord::generateSyncedStringRepresentation() const {
		// Replace the old value with the new.
		std::stringstream ss;

		if (cvar.getType() == sani::cvarlang::ValueType::StringVal) {
			String value;
			cvar.read(value);

			ss << value;
		} else if (cvar.getType() == sani::cvarlang::ValueType::IntVal) {
			int32 value = 0;
			cvar.read(value);

			ss << value;
		} else if (cvar.getType() == sani::cvarlang::ValueType::FloatVal) {
			float32 value = 0.0f;
			cvar.read(value);

			ss << value;
		} else if (cvar.getType() == sani::cvarlang::ValueType::DoubleVal) {
			float64 value = 0.0;
			cvar.read(value);

			ss << value;
		}

		// Create the new representation.
		const String newValue = ss.str();
		String newRepresentation = token.getLine();

		if (newValue.size() < originalValue.size()) {
			// Remove chars.
			const size_t diff = originalValue.size() - newValue.size();

			newRepresentation.erase(indexOfValue, diff);
		} else if (newValue.size() > originalValue.size()) {
			// Add chars.
			const size_t diff = newValue.size() - originalValue.size();
			
			String insertion;
			insertion.resize(diff, ' ');

			newRepresentation.insert(indexOfValue, insertion);
		}

		newRepresentation.replace(indexOfValue, newValue.size(), newValue);

		return newRepresentation;
	}
	bool CVarRecord::shouldSync() const {
		return cvar.isSynced() && cvar.hasChanged();
	}

	CVarRecord::~CVarRecord() {
	}
}