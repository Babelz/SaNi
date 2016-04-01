#include "sani/engine/services/contracts/file_system_service_contract.hpp"
#include "sani/engine/messaging/messages/document_message.hpp"
#include "sani/engine/messaging/messages/query_message.hpp"
#include "sani/engine/messaging/messages/command_message.hpp"
#include "sani/engine/services/contracts/cvar_service_contract.hpp"
#include "sani/engine/messaging/state_message.hpp"
#include "sani/engine/services/cvar_service.hpp"
#include "sani/engine/sani_engine.hpp"
#include "sani/core/cvar/cvar_file.hpp"
#include "sani/core/cvar/cvar_compiler.hpp"
#include "sani/core/cvar/cvar_linker.hpp"
#include "sani/core/cvar/link_record.hpp"
#include "sani/engine/services/service_logging.hpp"
#include "sani/core/logging/log.hpp"

#include <sstream>

namespace sani {

	namespace engine {
		
		namespace services {

			using namespace cvarservice;

			CVarService::CVarService(SaNiEngine* const engine) : EngineService("cvar service", engine) {
			}

			bool CVarService::onStart() {
				return initialize();
			}
			void CVarService::onTerminate() {
				syncCVars();
			}

			void CVarService::handleDocumentMessage(messages::DocumentMessage* const message) {
				const CVarServiceCommands command = static_cast<CVarServiceCommands>(message->getCommand());

				switch (command) {
				case CVarServiceCommands::ListCVars:
					listCVars(message);
					return;
				default:
					// TODO: dead letter.
					return;
				}
			}
			void CVarService::handleQueryMessage(messages::QueryMessage* const message) {
				const CVarServiceCommands command = static_cast<CVarServiceCommands>(message->getCommand());

				switch (command) {
				case CVarServiceCommands::GetCVar:
					getCVar(message);
					return;
				default:
					LOG_DEAD_LETTER(message);
					return;
				}
			}

			bool CVarService::initialize() {
				SaNiEngine* const engine = getEngine();
				
				// Attempt to open the configuration file.
				auto openFile = engine->createEmptyMessage<messages::QueryMessage>();
				filesystemservice::openFile(openFile, "config\\main.cfg", io::Filemode::Read);
				engine->routeMessage(openFile);

				if (openFile->success()) {
					// Got the file, load the config from it and close it.
					auto closeFile = engine->createEmptyMessage<messages::CommandMessage>();
					filesystemservice::closeFile(closeFile, "config\\main.cfg");
					engine->routeMessage(closeFile);

					loadConfig();

					// Close the file.
					engine->releaseMessage(closeFile);

					configuration.isDefault = false;

					FNCLOG_INF(log::OutFlags::All, "user defined cvar configuration loaded");
				} else {
					// No config file was defined, generate a default config.
					generateDefaultConfig();

					configuration.isDefault = true;
					
					FNCLOG_WRN(log::OutFlags::All, "default cvar configuration in use");
				}
				
				engine->releaseMessage(openFile);
				
				// Initialization should never fail, either the user defined file gets loaded 
				// or the default config.
				return true;
			}
			void CVarService::syncCVars() {
				if (!configuration.canSync) return;
				if (records.size() == 0)	return;
				
				SaNiEngine* engine = getEngine();
				
				String currentFilename;
				CVarFile file;

				io::FileStream* stream = nullptr;
				
				for (CVarRecord& record : records) {
					// Swap or open file for the first time.
					if (record.getFilename() != currentFilename) {
						auto openFile = engine->createEmptyMessage<messages::QueryMessage>();
						
						filesystemservice::openFile(openFile, ConfigRoot + record.getFilename(), io::Filemode::Truncate);
						
						engine->routeMessage(openFile);
						
						SANI_ASSERT(openFile->wasHandled());

						if (stream != nullptr) {
							syncFile(file, stream, currentFilename);
						}

						stream = static_cast<io::FileStream*>(openFile->getResults());

						engine->releaseMessage(openFile);
						
						currentFilename = record.getFilename();

						auto search = std::find_if(cvarFiles.begin(), cvarFiles.end(), [&currentFilename](const CVarFile& cvarFile) {
							return currentFilename == cvarFile.getFilename();
						});

						if (search == cvarFiles.end()) {
							std::stringstream ss;

							ss << "could not sync cvar " << "\"" << record.getCVarName() << "\"" << ", file not found";

							FNCLOG_ERR(sani::log::OutFlags::All, ss.str());
							
							continue;
						}

						file = *search;
					}

					if (record.shouldSync()) {
						// Sync.
						file.overwriteLineAtIndex(record.getLineNumber(), record.generateSyncedStringRepresentation());
					}
				}

				syncFile(file, stream, currentFilename);

				auto closeFile = engine->createEmptyMessage<messages::CommandMessage>();
				filesystemservice::closeFile(closeFile, ConfigRoot + currentFilename);
				engine->routeMessage(closeFile);
				SANI_ASSERT(closeFile->wasHandled());

				engine->releaseMessage(closeFile);
			}

			void CVarService::syncFile(CVarFile &file, io::FileStream* stream, String currentFilename)
			{
				SaNiEngine* engine = getEngine();

				for (uint32 i = 0; i < file.getLinesCount(); i++) {
					const String line = file.lineAtIndex(i) + '\n';

					const unsigned char* cstr = reinterpret_cast<const unsigned char*>(line.c_str());
					
					stream->write(cstr, static_cast<uint32>(line.size()));
				}

				auto closeFile = engine->createEmptyMessage<messages::CommandMessage>();
				filesystemservice::closeFile(closeFile, ConfigRoot + currentFilename);
				engine->routeMessage(closeFile);
				SANI_ASSERT(closeFile->wasHandled());

				engine->releaseMessage(closeFile);
			}

			void CVarService::generateDefaultConfig() {
				// This is the default configuration that 
				// games with no cvar file need to use.
				const String defaultConfiguration(
					"volatile window_width 1280\n"
					"volatile window_height 720\n"
					""
					"volatile backbuffer_width 1280\n"
					"volatile backbuffer_height 720\n"
					""
					"volatile samples_count 8\n"
					""
					"volatile stretch_backbuffer 1\n"
				);

				std::list<CVarFile> cvarFiles;
				cvarFiles.push_back(CVarFile("main.cfg", defaultConfiguration));

				compile(cvarFiles);
			}
			void CVarService::loadConfig() {
				SaNiEngine* const engine = getEngine();

				// List all cvar files we can find.
				auto listFiles = engine->createEmptyMessage<messages::QueryMessage>();
				filesystemservice::listFiles(listFiles, Config);
				engine->routeMessage(listFiles);
				SANI_ASSERT(listFiles->wasHandled());

				std::vector<String>* files = static_cast<std::vector<String>*>(listFiles->getResults());

				// Get contents of each file.
				for (const String& file : *files) {
					// Open file.
					auto openFile = engine->createEmptyMessage<messages::QueryMessage>();
					filesystemservice::openFile(openFile, ConfigRoot + file, io::Filemode::Read);
					engine->routeMessage(openFile);
					SANI_ASSERT(openFile->wasHandled());
					
					// Get the data string aka files contents.
					auto getFileDataString = engine->createEmptyMessage<messages::QueryMessage>();
					filesystemservice::getFileDataString(getFileDataString, ConfigRoot + file);
					engine->routeMessage(getFileDataString);
					SANI_ASSERT(getFileDataString->wasHandled());

					// Close the file.
					auto closeFile = engine->createEmptyMessage<messages::CommandMessage>();
					filesystemservice::closeFile(closeFile, ConfigRoot + file);
					engine->routeMessage(closeFile);
					SANI_ASSERT(closeFile->wasHandled());

					// Get the contents.
					String* contents = static_cast<String*>(getFileDataString->getResults());
					cvarFiles.push_back(CVarFile(file, *contents));

					// Release messages that have been processed.
					engine->releaseMessage(openFile);
					engine->releaseMessage(getFileDataString);
					engine->releaseMessage(closeFile);

					// Deallocate shared contents string.
					engine->deallocateShared(contents);
				}

				engine->releaseMessage(listFiles);

				// Deallocate shared files vector.
				engine->deallocateShared(files);

				// "Compile" all cvar files that we could find.
				compile(cvarFiles);
			}

			void CVarService::compile(std::list<CVarFile>& files) {
				const String mainFileName("main.cfg");

				LinkRecord record;

				CVarLinker linker;
				linker.link(mainFileName, files, &record);

				CVarCompiler compiler;
				compiler.compile(mainFileName, files, cvars, records);
			}

			void CVarService::getCVar(messages::QueryMessage* const message) {
				const String& name = message->getContents();

				auto it = std::find_if(cvars.begin(), cvars.end(), [&name](CVar& cvar) {
					return cvar.getName() == name;
				});

				if (it != cvars.end()) message->setResults(&*it);

				message->markHandled();
			}

			void CVarService::listCVars(messages::DocumentMessage* const message) {
				std::vector<CVar* const>* cvars = getEngine()->allocateShared<std::vector<CVar* const>>();
				NEW_DYNAMIC_DEFAULT(std::vector<CVar* const>, cvars);

				for (CVar& cvar : this->cvars) cvars->push_back(&cvar);

				message->setData(cvars);
				message->markHandled();
			}

			void CVarService::receive(messages::Message* const message) {
				const MessageType messageType = message->getType();
				
				switch (messageType) {
				case MessageType::Query:
					handleQueryMessage(static_cast<messages::QueryMessage*>(message));
					break;
				case MessageType::Document:
					handleDocumentMessage(static_cast<messages::DocumentMessage*>(message));
					break;
				default:
					LOG_DEAD_LETTER(message);
					break;
				}
			}
		}
	}
}