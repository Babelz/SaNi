#include "sani/engine/services/contracts/file_system_service_contract.hpp"
#include "sani/engine/messaging/messages/command_message.hpp"
#include "sani/engine/messaging/messages/query_message.hpp"
#include "sani/engine/services/file_system_service.hpp"
#include "sani/engine/sani_engine.hpp"
#include "sani/core/utils/string_utils.hpp"

namespace sani {

	namespace engine {
		
		namespace services {

			using namespace filesystemservice;
			using namespace sani::io;

			FileSystemService::FileSystemService(SaNiEngine* const engine) : EngineService("file system service", engine) {
			}

			void FileSystemService::handleQueryMessage(messages::QueryMessage* const message) {
				const FilesystemServiceCommands command = static_cast<FilesystemServiceCommands>(message->getCommand());

				switch (command) {
				case FilesystemServiceCommands::FileExists:
					fileExists(message);
					return;
				case FilesystemServiceCommands::OpenFile:
					openFile(message);
					return;
				case FilesystemServiceCommands::IsAbsolutePath:
					isAbsolutePath(message);
					return;
				case FilesystemServiceCommands::GetFileDataString:
					getFileDataString(message);
					return;
				case FilesystemServiceCommands::GetFileData:
					getFileData(message);
					return;
				default:
					// TODO: dead letter.
					return;
				}
			}
			void FileSystemService::handleCommandMessage(messages::CommandMessage* const message) {
				const FilesystemServiceCommands command = static_cast<FilesystemServiceCommands>(message->getCommand());
				
				switch (command) {
				case FilesystemServiceCommands::CloseFile:
					closeFile(message);
					return;
				default:
					// TODO: dead letter.
					return;
				}
			}

			void FileSystemService::fileExists(messages::QueryMessage* const message) {
				bool* result = getEngine()->allocateShared<bool>();
				
				*result = fileSystem.fileExists(message->getContents());
				
				message->setResults(result);
				message->markHandled();
			}
			void FileSystemService::openFile(messages::QueryMessage* const message) {
				std::vector<String> tokens;

				FileStream* fileStream = nullptr;

			}
			void FileSystemService::closeFile(messages::CommandMessage* const message) {
			}

			void FileSystemService::isAbsolutePath(messages::QueryMessage* const message) {
			}

			void FileSystemService::getFileData(messages::QueryMessage* const message) {
			}
			void FileSystemService::getFileDataString(messages::QueryMessage* const message) {
			}

			void FileSystemService::listFiles(messages::QueryMessage* const message) {
			}

			void FileSystemService::receive(messages::Message* const message) {
				const MessageType messageType = message->getType();

				switch (messageType) {
				case MessageType::Query:
					handleQueryMessage(static_cast<messages::QueryMessage*>(message));
					break;
				case MessageType::Command:
					handleCommandMessage(static_cast<messages::CommandMessage*>(message));
					break;
				default:
					break;
				}
			}
		}
	}
}