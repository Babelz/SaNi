#pragma once

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

	class CVarParser {
	public:
		CVarParser();

		void parse();
		
		~CVarParser();
	};
}