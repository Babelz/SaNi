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

namespace sani {

	namespace engine {
		
		namespace services {

			using namespace cvarservice;

			CVarService::CVarService(SaNiEngine* const engine) : EngineService("cvar service", engine) {
			}

			void CVarService::handleStateMessage(StateMessage* const message) {
				if (message->oldState == ServiceState::Uninitialized)		initialize();
				else if (message->newState == ServiceState::Terminated)		syncCVars();

				EngineService::handleStateMessage(message);
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
				case CVarServiceCommands::ContainsCVar:
					containsCVar(message);
					return;
				default:
					// TODO: dead letter.
					return;
				}
			}

			/*
				TODO: remove duplicated messages.
			*/

			void CVarService::initialize() {
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
				} else {
					// No config file was defined, generate a default config.
					generateDefaultConfig();

					configuration.isDefault = true;
				}
				
				engine->releaseMessage(openFile);
			}
			void CVarService::syncCVars() {
				if (configuration.canSync) {
					// TODO: sync cvars.
				}
			}

			void CVarService::generateDefaultConfig() {
				// TODO: impl default config.
				//throw std::runtime_error("not implemented");
				const String defaultCVarConfiguration(
					"window_width 1280\n"
					"window_height 720\n"
					"back_buffer_width 1280\n"
					"back_buffer_height 720\n"
				);
			}
			void CVarService::loadConfig() {
				const String config("config");

				const String configRoot(config + "\\");
				
				SaNiEngine* const engine = getEngine();

				// List all cvar files we can find.
				auto listFiles = engine->createEmptyMessage<messages::QueryMessage>();
				filesystemservice::listFiles(listFiles, config);
				engine->routeMessage(listFiles);
				SANI_ASSERT(listFiles->wasHandled());

				std::vector<String>* files = static_cast<std::vector<String>*>(listFiles->getResults());
				std::list<CVarFile> cvarFiles;

				// Get contents of each file.
				for (const String& file : *files) {
					// Open file.
					auto openFile = engine->createEmptyMessage<messages::QueryMessage>();
					filesystemservice::openFile(openFile, configRoot + file, io::Filemode::Read);
					engine->routeMessage(openFile);
					SANI_ASSERT(openFile->wasHandled());
					
					// Get the data string aka files contents.
					auto getFileDataString = engine->createEmptyMessage<messages::QueryMessage>();
					filesystemservice::getFileDataString(getFileDataString, configRoot + file);
					engine->routeMessage(getFileDataString);
					SANI_ASSERT(getFileDataString->wasHandled());

					// Close the file.
					auto closeFile = engine->createEmptyMessage<messages::CommandMessage>();
					filesystemservice::closeFile(closeFile, configRoot + file);
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

				// Deallocate shared fiels vector.
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

			void CVarService::containsCVar(messages::QueryMessage* const message) {
				bool* result = getEngine()->allocateShared<bool>();
				const String& name = message->getContents();

				auto it = std::find_if(cvars.begin(), cvars.end(), [&name](CVar& cvar) {
					return cvar.getName() == name;
				});

				if (it != cvars.end()) *result = true;

				message->setResults(result);
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
					break;
				}
			}
		}
	}
}