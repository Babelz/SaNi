#include "sani/engine/services/file_system_service.hpp"
#include "sani/engine/services/cvar_service.hpp"
#include "sani/core/cvar/cvar_compiler.hpp"
#include "sani/core/cvar/cvar_file.hpp"
#include "sani/engine/sani_engine.hpp"

namespace sani {

	namespace engine {

		CVarService::CVarService(SaNiEngine* const engine) : EngineService("cvar", engine) {
		}

		void CVarService::useUserDefinedConfiguration() {
			std::vector<String, std::allocator<String>> cvarFiles;
			fileSystem.listFiles(cvarFiles, configurationRootFolder);

			// Read lines and save paths.
			for (String& filename : cvarFiles) {

				// Check if the file is a .cfg, if not, don't parse it.
				const String ending(".cfg");

				if (filename.substr(filename.size() - ending.size(), ending.size()) == ending) {
					// Open files.
					const String path(configurationRootFolder + "\\" + filename);

					if (!fileSystem.isFileOpen(path)) {
						sani::io::FileStream* stream;

						fileSystem.openFile(path, io::Filemode::Read, &stream);
					}

					// Just assume the file is open.
					const String contents(fileSystem.getFileDataString(path));

					// Create new file record from the data collected.
					files.push_back(CVarFile(path, contents));

					// Close after reading.
					fileSystem.closeFile(path);
				}
			}
		}
		void CVarService::useDefaultConfiguration() {
			char* contents = "graphics_resolution_width		1280"
							 "graphics_resolution_height	720";

			CVarFile file("configuration\\main.cfg", contents);
			CVarCompiler compiler;

			std::list<CVarFile> files;
			files.push_back(file);

			compiler.compile(file.getFilename(), files, cvars, records);
		}
		void CVarService::checkForRequiredCVars() {
		}

		bool CVarService::onInitialize() {
			FileSystemService* const fileSystemService = static_cast<FileSystemService*>(getEngine()->locateService("file system"));
			use(fileSystemService);

			if (!fileSystemService->fileExists("configuration\\main.cfg")) {
				// No configuration main defined, use default configuration.
				useDefaultConfiguration();
			} else {
				useUserDefinedConfiguration();
			}
		}

		void CVarService::onStop() {
		}

		CVar* const CVarService::findCVar(const String& name) {
		}

		CVarService::~CVarService() {
		}
	}
}