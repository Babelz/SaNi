#pragma once

#include "sani/core/interfaces/error_logger.hpp"
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

	using StatementList = std::list<CVarRequireStatement>;
	using RecordList	= std::list<CVarRecord>;
	using TokenList		= std::list<CVarToken>;
	using CVarList		= std::list<CVar>;

	SANI_FORWARD_DECLARE_STRUCT_1(cvarlang, IntermediateCVar);
	SANI_FORWARD_DECLARE_STRUCT_1(cvarlang, IntermediateCondition);
	SANI_FORWARD_DECLARE_STRUCT_1(cvarlang, IntermediateRequireStatement);
	
	SANI_FORWARD_DECLARE(CVarParser);
	SANI_FORWARD_DECLARE(CVarTokenizer);
	SANI_FORWARD_DECLARE(CVarLinker);

	using namespace interfaces;

	/// @class CVarCompiler cvar_compiler.hpp "sani/core/cvar/cvar_compiler.hpp"
	/// @author voidbab
	///
	/// Class that turns configuration source data into usable
	/// cvars and requirements.
	class CVarCompiler final : public ErrorLogger {
	private:
		using StatementGeneratorCondition = std::function<bool(const IntermediateCondition&)>;
		using StatementGenerator		  = std::function<void(const IntermediateCondition&, Condition&, CVarList&)>;

		struct RequireStatementGenerator {
			const StatementGeneratorCondition condition;
			const StatementGenerator generate;

			RequireStatementGenerator(const StatementGeneratorCondition condition, StatementGenerator generate) : condition(condition),
																												  generate(generate) {
			}
		};

		std::list<RequireStatementGenerator> statementGenerators;

		void checkIfIsRedeclaration(CVarList& cvars, CVarToken& token, IntermediateCVar& intermediateCVar);
		bool containsCVar(CVarList& cvars, const String& name) const;

		/// Generates cvars and records.
		void compile(CVarList& cvars, RecordList& records, TokenList& tokens);
		
		/// Generates a cvar.
		void generateCVar(CVarList& cvars, StatementList& statements, const IntermediateCVar* intermediateCVar) const;
		/// Generates a record for given cvar.
		void generateRecord(RecordList& records, const CVarToken& token, const CVar& cvar) const;

		/// Generates a require statement.
		void generateRequireStatement(StatementList& statements, CVarList& cvars, const IntermediateRequireStatement* intermediateRequireStatement);
		/// Generates an expression using two constant values.
		void generateConstConstExpression(const IntermediateCondition& intermediateCondition, Condition& condition, CVarList& cvars) const;
		/// Generates a const cvar expression.
		void generateConstCVarExpression(const IntermediateCondition& intermediateCondition, Condition& condition, CVarList& cvars) const;
		/// Generates a cvar const expression.
		void generateCVarConstExpression(const IntermediateCondition& intermediateCondition, Condition& condition, CVarList& cvars);
		/// Generates a const bool cvar expression.
		void generateConstCVarBoolExpression(const IntermediateCondition& intermediateCondition, Condition& condition, CVarList& cvars);
		/// Generates a const bool const expression.
		void generateConstBoolConstExpression(const IntermediateCondition& intermediateCondition, Condition& condition, CVarList& cvars) const;
		void generateCVarCVarExpression(const IntermediateCondition& intermediateCondition, Condition& condition, CVarList& cvars);
		
		void generateCondition(const IntermediateCondition& intermediateCondition, Condition& condition, CVar& lhs, CVar& rhs) const;

		CVar* findCVar(CVarList& cvars, const String& name);
	
		void generateStatementGenerators();
	public:
		CVarCompiler();

		/// Compiles all given files.
		/// @param[in] file file that should be compiled
		/// @param[in] files cvar source files
		/// @param[in] cvars generated cvars
		/// @param[in] records generated records
		void compile(const String& filename, std::list<CVarFile>& files, std::list<CVar>& cvars, std::list<CVarRecord>& records);
		
		~CVarCompiler();
	}; 
	
	#define GEN_REQUIRE_STATEMENT_GENERATOR(condition, generate) RequireStatementGenerator([](const IntermediateCondition& intermediateCondition) { return condition; }, generate) 
}