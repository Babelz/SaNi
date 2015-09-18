#pragma once

#include "sani/core/cvar/cvar_record.hpp"
#include "sani/core/cvar/cvar_file.hpp"
#include <vector>

namespace sani {

	/// @class CVarRecordGenerator cvar_record_generator.hpp "sani/core/cvar/cvar_record_generator.hpp"
	/// @author voidbab
	///
	/// Class that generates syncable cvar records.
	class CVarRecordGenerator {
	public:
		CVarRecordGenerator();

		void generateRecords(std::vector<CVarFile>& files, std::vector<CVarRecord>& outRecords);

		~CVarRecordGenerator();
	};
}