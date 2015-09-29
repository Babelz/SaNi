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

/*
	Error handling levels:
		- Tokenizer handles syntax errors
		- Parser handles logical errors
		- Compiler keeps watch of the scope. Will emit error if 
		  require scopes are not closed.

		  Will emit error if a cvar is undefined at given compilation time.
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

		void generateCVars(std::list<CVar>& cvars, std::list<CVarRecord>& records, std::list<CVarToken>& tokens);
		
		void generateCVar(std::list<CVar>& cvars, std::list<CVarRequireStatement>& statements, const cvarlang::IntermediateCVar* intermediateCVar);
		void generateRecord(std::list<CVarRecord>& records, const CVarToken& token, const CVar& cvar) const;

		void generateRequireStatement(std::list<CVarRequireStatement>& statements, std::list<CVar>& cvars, const cvarlang::IntermediateRequireStatement* intermediateRequireStatement);
	
		void generateConstConstExpression(const cvarlang::IntermediateCondition* intermediateCondition, Condition& condition);
		void generateConstCVarExpression(const cvarlang::IntermediateCondition* intermediateCondition, Condition& condition, std::list<CVar>& cvars);
		void generateCVarConstExpression(const cvarlang::IntermediateCondition* intermediateCondition, Condition& condition, std::list<CVar>& cvars);
		void generateConstCVarBoolExpression(const cvarlang::IntermediateCondition* intermediateCondition, Condition& condition, std::list<CVar>& cvars);
		void generateConstBoolConstExpression(const cvarlang::IntermediateCondition* intermediateCondition, Condition& condition, std::list<CVar>& cvars);
		void generateCVarCVarExpression(const cvarlang::IntermediateCondition* intermediateCondition, Condition& condition, std::list<CVar>& cvars);

		void generateCondition(const cvarlang::IntermediateCondition* intermediateCondition, Condition& condition, CVar& lhs, CVar& rhs);
	public:
		CVarCompiler();

		bool hasErrors() const;
		String getNextError();

		void compile(std::list<CVarFile>& files, std::list<CVar>& cvars, std::list<CVarRecord>& records, const bool synced);
		
		~CVarCompiler();
	}; 
}