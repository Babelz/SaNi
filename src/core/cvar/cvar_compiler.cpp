#include "sani/core/cvar/cvar_record_generator.hpp"
#include "sani/core/cvar/cvar_tokenizer.hpp"
#include "sani/core/cvar/cvar_emitter.hpp"
#include "sani/core/cvar/cvar_loader.hpp"
#include "sani/core/cvar/cvar_compiler.hpp"
#include "sani/platform/file_system.hpp"

namespace sani {

	CvarCompiler::CvarCompiler(const String& configurationRootFolder, io::FileSystem& fileSystem) : configurationRootFolder(configurationRootFolder),
																						        fileSystem(fileSystem) {
	}

	void CvarCompiler::parse() {
		// Load all files.
		CVarLoader loader(configurationRootFolder, fileSystem);
		
		std::list<CVarFile> files;
		loader.load(files);

		// Generate tokens from lines.
		CVarTokenizer tokenizer;

		std::list<CVarToken> tokens;
		tokenizer.tokenize(files, tokens);

		// Generate cvars.
		CVarEmitter emitter;
		emitter.emit(tokens, cvars);
		
		// Generate records.
		CVarRecordGenerator recordGenerator;
		recordGenerator.generateRecords(tokens, cvars, records);
	}

	std::list<CVarRecord>& CvarCompiler::getRecords() {
		return records;
	}
	std::list<CVar>& CvarCompiler::getCVars() {
		return cvars;
	}

	CvarCompiler::~CvarCompiler() {
	}
}