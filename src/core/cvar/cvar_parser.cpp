#include "sani/core/cvar/cvar_record_generator.hpp"
#include "sani/core/cvar/cvar_tokenizer.hpp"
#include "sani/core/cvar/cvar_emitter.hpp"
#include "sani/core/cvar/cvar_loader.hpp"
#include "sani/core/cvar/cvar_parser.hpp"
#include "sani/platform/file_system.hpp"

namespace sani {

	CVarParser::CVarParser(const String& configurationRootFolder, io::FileSystem& fileSystem) : configurationRootFolder(configurationRootFolder),
																						        fileSystem(fileSystem) {
	}

	void CVarParser::parse() {
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

	std::list<CVarRecord>& CVarParser::getRecords() {
		return records;
	}
	std::list<CVar>& CVarParser::getCVars() {
		return cvars;
	}

	CVarParser::~CVarParser() {
	}
}