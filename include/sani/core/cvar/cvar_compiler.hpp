#pragma once

#include "sani/core/cvar/cvar_record.hpp"
#include "sani/core/cvar/cvar_token.hpp"
#include "sani/forward_declare.hpp"
#include <stack>
#include <list>

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

	typedef	std::stack<String> ErrorBuffer;

	SANI_FORWARD_DECLARE_STRUCT_1(cvarlang, IntermediateCVar);
	SANI_FORWARD_DECLARE_STRUCT_1(cvarlang, IntermediateCondition);
	SANI_FORWARD_DECLARE_STRUCT_1(cvarlang, IntermediateRequireStatement);
	
	class CVarParser;
	class CVarTokenizer;

	class CVarCompiler {
	private:
		ErrorBuffer errorBuffer;
		bool synced;

		void copyErrors(CVarParser* parser);
		void copyErrors(CVarTokenizer* tokenizer);

		void pushError(const String& message);

		void generateCVars(std::list<CVar>& cvars, std::list<CVarRecord>& records, std::list<CVarToken>& tokens);
		
		void generateCVar(std::list<CVar>& cvars, std::list<CVarRequireStatement>& statements, const cvarlang::IntermediateCVar* intermediateCVar);
		void generateRecord(std::list<CVarRecord>& records, const CVarToken& token, const CVar& cvar) const;

		void generateRequireStatement(std::list<CVarRequireStatement>& statements, std::list<CVar>& cvars, const cvarlang::IntermediateRequireStatement* intermediateRequireStatement);
	
		Condition generateConstConstExpression(const cvarlang::IntermediateCondition* condition);
		Condition generateConstCVarExpression(const cvarlang::IntermediateCondition* condition, std::list<CVar>& cvars);
		Condition generateCVarConstExpression(const cvarlang::IntermediateCondition* condition, std::list<CVar>& cvars);
		Condition generateConstCVarBoolExpression(const cvarlang::IntermediateCondition* condition, std::list<CVar>& cvars);
		Condition generateConstBoolConstExpression(const cvarlang::IntermediateCondition* condition, std::list<CVar>& cvars);
	public:
		CVarCompiler();

		bool hasErrors() const;
		String getNextError();

		void compile(std::list<CVarFile>& files, std::list<CVar>& cvars, std::list<CVarRecord>& records, const bool synced);
		
		~CVarCompiler();
	};
}