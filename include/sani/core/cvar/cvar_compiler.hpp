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

	using namespace sani::cvarlang;

	typedef std::list<CVarRequireStatement> StatementList;
	typedef std::list<CVarRecord> RecordList;
	typedef std::list<CVarToken> TokenList;
	typedef	std::stack<String> ErrorBuffer;
	typedef std::list<CVar> CVarList;

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
		void generateCVars(CVarList& cvars, RecordList& records, TokenList& tokens);
		
		/// Generates a cvar.
		void generateCVar(CVarList& cvars, StatementList& statements, const IntermediateCVar* intermediateCVar) const;
		/// Generates a record for given cvar.
		void generateRecord(RecordList& records, const CVarToken& token, const CVar& cvar) const;

		/// Generates a require statement.
		void generateRequireStatement(StatementList& statements, CVarList& cvars, const IntermediateRequireStatement* intermediateRequireStatement);
		/// Generates an expression using two constant values.
		void generateConstConstExpression(const IntermediateCondition* intermediateCondition, Condition& condition) const;
		/// Generates a const cvar expression.
		void generateConstCVarExpression(const IntermediateCondition* intermediateCondition, Condition& condition, CVarList& cvars) const;
		/// Generates a cvar const expression.
		void generateCVarConstExpression(const IntermediateCondition* intermediateCondition, Condition& condition, CVarList& cvars);
		/// Generates a const bool cvar expression.
		void generateConstCVarBoolExpression(const IntermediateCondition* intermediateCondition, Condition& condition, CVarList& cvars);
		/// Generates a const bool const expression.
		void generateConstBoolConstExpression(const IntermediateCondition* intermediateCondition, Condition& condition, CVarList& cvars) const;
		void generateCVarCVarExpression(const IntermediateCondition* intermediateCondition, Condition& condition, CVarList& cvars);
		
		void generateCondition(const IntermediateCondition* intermediateCondition, Condition& condition, CVar& lhs, CVar& rhs) const;

		CVar* findCVar(CVarList& cvars, const String& name);
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
	
	#define IS_CONST_CVAR_BOOL_EXPRESSION(intermediateCondition) 
	#define IS_CONST_BOOL_CONST_EXPRESSION(intermediateCondition) 
	#define IS_CONST_CONST_EXPRESSION(intermediateCondition) 
	#define IS_CONST_CVAR_EXPRESSION(intermediateCondition) 
	#define IS_CVAR_CVAR_EXPRESSION(intermediateCondition) 
}