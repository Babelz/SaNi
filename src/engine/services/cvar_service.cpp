#include "sani/engine/services/file_system_service.hpp"
#include "sani/engine/services/cvar_service.hpp"
#include "sani/core/cvar/cvar_compiler.hpp"
#include "sani/engine/sani_engine.hpp"

namespace sani {

	namespace engine {

		const String configurationRootFolder = "configuration";

		CVarService::CVarService(SaNiEngine* const engine) : EngineService("cvar", engine),
															 fileSystemService(nullptr) {
		}

		void CVarService::loadFiles() {
			std::vector<String, std::allocator<String>> cvarFiles;
			fileSystemService->listFiles(cvarFiles, configurationRootFolder);

			// Read lines and save paths.
			for (String& filename : cvarFiles) {

				// Check if the file is a .cfg, if not, don't parse it.
				const String ending(".cfg");

				if (filename.substr(filename.size() - ending.size(), ending.size()) == ending) {
					// Open files.
					const String path(configurationRootFolder + "\\" + filename);

					if (!fileSystemService->isFileOpen(path)) {
						sani::io::FileStream* stream;

						fileSystemService->openFile(path, io::Filemode::Read, &stream);
					}

					// Just assume the file is open.
					const String contents(fileSystemService->getFileDataString(path));

					// Create new file record from the data collected.
					files.push_back(CVarFile(path, contents));

					// Close after reading.
					fileSystemService->closeFile(path);
				}
			}
		}

		void CVarService::useUserDefinedConfiguration() {
			loadFiles();

			CVarCompiler compiler;
			compiler.compile(files.begin()->getFilename(), files, cvars, records);
		}
		void CVarService::useDefaultConfiguration() {
			char* contents = "graphics_resolution_width 1280\n"
							 "graphics_resolution_height 720\n";

			CVarFile file("configuration\\main.cfg", contents);
			CVarCompiler compiler;

			files.push_back(file);

			compiler.compile(file.getFilename(), files, cvars, records);
		}
		void CVarService::checkForRequiredCVars() {
		}

		void CVarService::onInitialize() {
			fileSystemService = static_cast<FileSystemService*>(getEngine()->locateService("file system"));
			use(fileSystemService);

			if (!fileSystemService->fileExists("configuration\\main.cfg")) {
				// No configuration main defined, use default configuration.
				useDefaultConfiguration();
			} else {
				useUserDefinedConfiguration();

				checkForRequiredCVars();
			}
		}

		void CVarService::onStop() {
			/*std::list<CVarFile* const> filesToSync;
			
			CVarFile& fileToSync = *files.begin();
			filesToSync.push_back(&fileToSync);

			for (const CVarRecord& record : records) {
				if (!record.shouldSync()) continue;

				if (fileToSync.getFilename() != record.getFilename()) {
					const String fileName = record.getFilename();

					fileToSync = *std::find_if(files.begin(), files.end(), [&fileName](const CVarFile& file) {
						return file.getFilename() == fileName;
					});
				}

				const String syncedRepresentation	= record.generateSyncedStringRepresentation();
				const uint32 linenumber				= record.getLineNumber();
				
				fileToSync.lineAtIndex(linenumber) = syncedRepresentation;
			}*/

			// TODO: add syncing.

			unuse(fileSystemService);
		}

		CVar* const CVarService::findCVar(const String& name) {
			auto result = std::find_if(cvars.begin(), cvars.end(), [&name](const CVar& cvar) {
				return cvar.getName() == name;
			});

			return nullptr;
			//return result == cvars.end() ? nullptr : &*result;
		}
	}
}