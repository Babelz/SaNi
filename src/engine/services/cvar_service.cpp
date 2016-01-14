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
				if (message->oldState == ServiceState::Uninitialized) {
					initialize();
				} else if (message->newState == ServiceState::Terminated) {
					syncCVars();
				}

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
				
				auto openFile = engine->createEmptyMessage<messages::QueryMessage>();
				filesystemservice::openFile(openFile, "config\\main.cfg", io::Filemode::Read);
				engine->routeMessage(openFile);

				if (openFile->success()) {
					auto closeFile = engine->createEmptyMessage<messages::CommandMessage>();
					filesystemservice::closeFile(closeFile, "config\\main.cfg");
					engine->routeMessage(closeFile);

					loadConfig();

					engine->releaseMessage(closeFile);
				} else {
					generateDefaultConfig();
				}
				
				engine->releaseMessage(openFile);
			}
			void CVarService::syncCVars() {
				// TODO: sync cvars.
			}

			void CVarService::generateDefaultConfig() {
				// TODO: impl default config.
				//throw std::runtime_error("not implemented");
			}
			void CVarService::loadConfig() {
				//// TODO: fix duplicated strings.
				SaNiEngine* const engine = getEngine();

				auto listFiles = engine->createEmptyMessage<messages::QueryMessage>();
				filesystemservice::listFiles(listFiles, "config");
				engine->routeMessage(listFiles);

				std::vector<String>* files = static_cast<std::vector<String>*>(listFiles->getResults());
				std::list<CVarFile> cvarFiles;

				for (const String& file : *files) {
					auto openFile = engine->createEmptyMessage<messages::QueryMessage>();
					filesystemservice::openFile(openFile, "config\\" + file, io::Filemode::Read);
					engine->routeMessage(openFile);
					
					auto getFileDataString = engine->createEmptyMessage<messages::QueryMessage>();
					filesystemservice::getFileDataString(getFileDataString, "config\\" + file);
					engine->routeMessage(getFileDataString);

					auto closeFile = engine->createEmptyMessage<messages::CommandMessage>();
					filesystemservice::closeFile(closeFile, "config\\" + file);
					engine->routeMessage(closeFile);

					String* contents = static_cast<String*>(getFileDataString->getResults());
					cvarFiles.push_back(CVarFile(file, *contents));

					engine->releaseMessage(openFile);
					engine->releaseMessage(getFileDataString);
					engine->releaseMessage(closeFile);

					engine->deallocateShared(contents);
				}

				engine->releaseMessage(listFiles);

				engine->deallocateShared(files);

				compile(cvarFiles);
			}

			void CVarService::compile(std::list<CVarFile>& files) {
				LinkRecord record;

				CVarLinker linker;
				linker.link("main.cfg", files, &record);

				CVarCompiler compiler;
				compiler.compile("main.cfg", files, cvars, records);
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
				NEW_DYNAMIC_DEFAULT<std::vector<CVar* const>>(cvars);

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