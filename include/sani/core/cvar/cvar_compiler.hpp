#pragma once

#include "sani/core/cvar/cvar_record.hpp"
#include "sani/core/cvar/cvar_token.hpp"
#include "sani/forward_declare.hpp"
#include "sani/core/cvar/cvar.hpp"
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

	SANI_FORWARD_DECLARE_1(io, FileSystem);
	SANI_FORWARD_DECLARE_STRUCT_1(cvarlang, IntermediateCVar);
	SANI_FORWARD_DECLARE_STRUCT_1(cvarlang, IntermediateRequireStatement);
	
	class CVarParser;
	class CVarTokenizer;

	class CVarCompiler {
	private:
		const String& configurationRootFolder;
		io::FileSystem& fileSystem;
		const bool synced;

		ErrorBuffer errorBuffer;

		void copyErrors(CVarParser* parser);
		void copyErrors(CVarTokenizer* tokenizer);

		void pushError(const String& message);

		void generateCVars(std::list<CVar>& cvars, std::list<CVarRecord>& records, std::list<CVarToken>& tokens);
		
		void generateCVar(std::list<CVar>& cvars, std::list<CVarRequireStatement>& statements, const cvarlang::IntermediateCVar* intermediateCVar) const;
		void generateRecord(std::list<CVarRecord>& records, const CVarToken& token, const CVar& cvar) const;

		void generateRequireStatement(std::list<CVarRequireStatement>& statements, const cvarlang::IntermediateRequireStatement* intermediateRequireStatement) const;
	public:
		CVarCompiler(const String& configurationRootFolder, io::FileSystem& fileSystem, const bool synced);

		bool hasErrors() const;
		String getNextError();

		void compile(std::list<CVar>& cvars, std::list<CVarRecord>& records);
		
		~CVarCompiler();
	};
}