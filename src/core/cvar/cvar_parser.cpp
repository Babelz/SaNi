#include "sani/core/cvar/cvar_parser.hpp"
#include "sani/core/utils/string_utils.hpp"

namespace sani {

	CVarParser::CVarParser() {
	}

	void CVarParser::parseCvar(String str, cvarlang::IntermediateCVar& intermediateCVar) const {
		std::vector<String> tokens;

		// Remove any comments, we don't need them here.
		if (cvarlang::lang::containsComment(str)) str = str.substr(str.find("\\", 0), 0);
	}
	void CVarParser::parseRequireStatement(String reqStr, const String& msgStr, cvarlang::IntermediateRequireStatement& IntermediateRequireStatement) const {
	}

	CVarParser::~CVarParser() {
	}
}