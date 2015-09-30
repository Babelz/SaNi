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

	/// @class CVarCompiler cvar_compiler.hpp "sani/core/cvar/cvar_compiler.hpp"
	/// @author voidbab
	///
	/// Class that turns configuration source data into usable
	/// cvars and requirements.
	class CVarCompiler {
	private:
		ErrorBuffer errorBuffer;
		bool synced;

		void copyErrors(CVarParser* parser);
		void copyErrors(CVarTokenizer* tokenizer);

		/// Generates cvars and records.
		void generateCVars(std::list<CVar>& cvars, std::list<CVarRecord>& records, std::list<CVarToken>& tokens);
		
		/// Generates a cvar.
		void generateCVar(std::list<CVar>& cvars, std::list<CVarRequireStatement>& statements, const cvarlang::IntermediateCVar* intermediateCVar) const;
		/// Generates a record for given cvar.
		void generateRecord(std::list<CVarRecord>& records, const CVarToken& token, const CVar& cvar) const;
		
		/// Generates a require statement.
		void generateRequireStatement(std::list<CVarRequireStatement>& statements, std::list<CVar>& cvars, const cvarlang::IntermediateRequireStatement* intermediateRequireStatement);
		/// Generates an expression using two constant values.
		void generateConstConstExpression(const cvarlang::IntermediateCondition* intermediateCondition, Condition& condition) const;
		/// Generates a const cvar expression.
		void generateConstCVarExpression(const cvarlang::IntermediateCondition* intermediateCondition, Condition& condition, std::list<CVar>& cvars) const;
		/// Generates a cvar const expression.
		void generateCVarConstExpression(const cvarlang::IntermediateCondition* intermediateCondition, Condition& condition, std::list<CVar>& cvars);
		/// Generates a const bool cvar expression.
		void generateConstCVarBoolExpression(const cvarlang::IntermediateCondition* intermediateCondition, Condition& condition, std::list<CVar>& cvars);
		/// Generates a constant bool expression using constant value.
		void generateConstBoolConstExpression(const cvarlang::IntermediateCondition* intermediateCondition, Condition& condition, std::list<CVar>& cvars) const;

		/// Generates a condition from given condition using given cvars.
		void generateCondition(const cvarlang::IntermediateCondition* intermediateCondition, Condition& condition, CVar& lhs, CVar& rhs) const;
	public:
		CVarCompiler();

		bool hasErrors() const;
		String getNextError();

		/// Compiles all given files.
		/// @param[in] files files to compile
		/// @param[in] cvars generated cvars
		/// @param[in] records generated records
		/// @param[in] synced should records be synced for this set.
		void compile(const std::list<CVarFile>& files, std::list<CVar>& cvars, std::list<CVarRecord>& records, const bool synced);
		
		~CVarCompiler();
	}; 
}