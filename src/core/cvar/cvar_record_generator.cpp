#include "sani/core/cvar/cvar_record_generator.hpp"

namespace sani {

	CVarRecordGenerator::CVarRecordGenerator() {
	}

	void CVarRecordGenerator::generateRecords(const std::list<CVarToken>& tokens, const std::list<CVar>& cvars, std::list<CVarRecord>& records) {
		for (const CVarToken& token : tokens) {
			// Skip all tokens that are not declarations.
			if (token.getType() != cvarlang::TokenType::Declaration) continue;;
			
		}
	}

	CVarRecordGenerator::~CVarRecordGenerator() {
	}
}