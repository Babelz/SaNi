#pragma once

#include "sani/core/cvar/cvar_record.hpp"
#include "sani/forward_declare.hpp"
#include "sani/core/cvar/cvar.hpp"
#include <vector>

/*
	Parsing steps:
		1) load ALL files
		2) generate tokens
		3) analyze tokens
		4) generate initial records
		5) link files
		6) generate tokens
			- requirements
			- cvars
		7) return cvar containers
*/

namespace sani {

	SANI_FORWARD_DECLARE_1(io, FileSystem);

	class CVarParser {
	private:
		const String& configurationRootFolder;
		io::FileSystem& fileSystem;

		std::vector<CVarRecord> records;
		std::vector<CVar> cvars;
	public:
		CVarParser(const String& configurationRootFolder, io::FileSystem& fileSystem);

		void parse();

		std::vector<CVarRecord>& getRecords() const;
		std::vector<CVar>& getCVars() const;
		
		~CVarParser();
	};
}