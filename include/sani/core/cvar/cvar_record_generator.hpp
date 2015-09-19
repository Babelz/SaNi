#pragma once

#include "sani/core/cvar/cvar_record.hpp"
#include "sani/core/cvar/cvar_file.hpp"
#include "sani/core/cvar/cvar.hpp"
#include <list>

namespace sani {

	/// @class CVarRecordGenerator cvar_record_generator.hpp "sani/core/cvar/cvar_record_generator.hpp"
	/// @author voidbab
	///
	/// Class that generates syncable cvar records.
	class CVarRecordGenerator {
	public:
		CVarRecordGenerator();

		void generateRecords(const std::list<CVarToken>& tokens, 
							 const std::list<CVar>& vars,
							 std::list<CVarRecord>& records);
		
		~CVarRecordGenerator();
	};
}