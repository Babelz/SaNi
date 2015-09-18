#include "sani/core/cvar/cvar_record.hpp"
#include <sstream>

namespace sani {

	CVarRecord::CVarRecord(const CVarToken& token, const CVar* cvar) : token(token),
																	   cvar(cvar) {
	}

	String CVarRecord::generateSyncedStringRepresentation() const {
		// Get get original representation.
		const uint32 lineNumber = token.getLineNumber();
		const String& original = token.getLine();

		// Replace the old value with the new.
		std::stringstream ss;
		
		if (cvar->getType() == sani::cvarlang::String) {
			String value;
			cvar->read(value);

			ss << value;
		}
		if (cvar->getType() == sani::cvarlang::Int) {
			int32 value = 0;
			cvar->read(value);

			ss << value;
		}
		if (cvar->getType() == sani::cvarlang::Float) {
			float32 value = 0.0f;
			cvar->read(value);

			ss << value;
		}
		if (cvar->getType() == sani::cvarlang::Double) {
			float64 value = 0.0;
			cvar->read(value);

			ss << value;
		}

		return ss.str();
	}
	bool CVarRecord::shouldSync() const {
		return cvar->isSynced() && cvar->hasChanged();
	}

	CVarRecord::~CVarRecord() {
	}
}