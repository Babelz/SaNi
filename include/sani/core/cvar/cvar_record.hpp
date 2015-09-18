#pragma once

#include "sani/core/cvar/cvar_token.hpp"
#include "sani/core/cvar/cvar.hpp"

namespace sani {

	/// @class CVarRecord cvar_record.hpp "sani/core/cvar/cvar_record.hpp"
	/// @author voidbab
	///
	/// Contains runtime and compile time information about cvars.
	/// Used to store cvars to files when the engine gets closed.
	class CVarRecord {
	private:
		const CVarToken token;		// Tokenized cvar.
		const CVar* cvar;			// Runtime cvar.
	public:
		CVarRecord(const CVarToken& token, const CVar* cvar);

		/// Creates a synced string representation of the underlying cvar.
		String generateSyncedStringRepresentation() const;
		/// Returns true if the record should be synced
		/// to the file where the cvar was loaded from.
		bool shouldSync() const;

		~CVarRecord();
	};
}