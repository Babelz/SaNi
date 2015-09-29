#include "sani/core/utils/string_utils.hpp"
#include "sani/core/cvar/cvar_record.hpp"
#include "sani/core/cvar/cvar_lang.hpp"
#include <sstream>

namespace sani {

	CVarRecord::CVarRecord(const CVarToken& token, const CVar& cvar) : token(token),
																	   cvar(cvar) {
		// Just find the original value, no need to do
		// any validation as we can except that the 
		// parsing system will fail at some point anyways 
		// if this token is invalid.
		std::vector<String> tokens;
		utils::split(token.getLine(), String(" "), tokens, true);

		if (tokens.size() >= 2) {
			originalValue = tokens[1];
			indexOfValue = token.getLine().find(originalValue);

			// Remove comments, trim.
			if (cvarlang::lang::containsComment(originalValue)) originalValue = originalValue.substr(0, originalValue.find("//"));
			
			utils::trim(originalValue);
		}
	}

	String CVarRecord::generateSyncedStringRepresentation() const {
		// Get get original representation.
		const uint32 lineNumber = token.getLineNumber();

		// Replace the old value with the new.
		std::stringstream ss;

		if (cvar.getType() == sani::cvarlang::StringVal) {
			String value;
			cvar.read(value);

			ss << value;
		} else if (cvar.getType() == sani::cvarlang::IntVal) {
			int32 value = 0;
			cvar.read(value);

			ss << value;
		} else if (cvar.getType() == sani::cvarlang::FloatVal) {
			float32 value = 0.0f;
			cvar.read(value);

			ss << value;
		} else if (cvar.getType() == sani::cvarlang::DoubleVal) {
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