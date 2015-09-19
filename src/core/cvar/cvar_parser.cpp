#include "sani/core/cvar/cvar_record_generator.hpp"
#include "sani/core/cvar/cvar_tokenizer.hpp"
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

		std::vector<CVarToken> tokens;
		tokenizer.tokenize(files, tokens);

		// Generate records.
		CVarRecordGenerator recordGenerator;
		recordGenerator.generateRecords(tokens, records);

		// Generate cvars.
		CVarEmitter emitter;
		emitter.emit(cvars);
	}

	std::vector<CVarRecord>& CVarParser::getRecords() const {
	}
	std::vector<CVar>& CVarParser::getCVars() const {
	}

	CVarParser::~CVarParser() {
	}
}