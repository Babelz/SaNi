#include "sani/engine/services/contracts/file_system_service_contract.hpp"
#include "sani/engine/messaging/messages/command_message.hpp"
#include "sani/engine/messaging/messages/query_message.hpp"
#include "sani/engine/services/file_system_service.hpp"
#include "sani/engine/sani_engine.hpp"
#include "sani/core/utils/string_utils.hpp"
#include "sani/core/utils/convert.hpp"

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
				utils::split(message->getContents(), "||", tokens, true);
				SANI_ASSERT(tokens.size() >= 2);

				const String& path = tokens[0];
				const Filemode filemode = static_cast<Filemode>(utils::toUInt32(tokens[1]));

				FileStream* fileStream = nullptr;
				
				fileSystem.openFile(path, filemode, &fileStream);

				message->setResults(fileStream);
				message->markHandled();
			}
			void FileSystemService::closeFile(messages::CommandMessage* const message) {
				const String& path = message->getData();

				fileSystem.closeFile(path);

				message->markHandled();
			}

			void FileSystemService::isAbsolutePath(messages::QueryMessage* const message) {
				bool* result = getEngine()->allocateShared<bool>();
				const String& path = message->getContents();

				*result = fileSystem.isAbsolutePath(path);

				message->setResults(result);
				message->markHandled();
			}

			void FileSystemService::getFileData(messages::QueryMessage* const message) {
				const String& path = message->getContents();
				FileStream* stream = nullptr;
				int64 size = 0;

				fileSystem.openFile(path, Filemode::Read, &stream);
				unsigned char* data = fileSystem.getFileData(path, size);
				
				message->setResults(message);
				message->markHandled();
			}
			void FileSystemService::getFileDataString(messages::QueryMessage* const message) {
				const String& path = message->getContents();

				const String fileContents = fileSystem.getFileDataString(path);
				String* result = getEngine()->allocateShared<String>();
				SANI_NEW_DYNAMIC_DEFAULT(String, result);

				message->setResults(result);
				message->markHandled();
			}

			void FileSystemService::listFiles(messages::QueryMessage* const message) {
				const String& path = message->getContents();
				std::vector<String>* files = getEngine()->allocateShared<std::vector<String>>();
				SANI_NEW_DYNAMIC_DEFAULT(std::vector<String>, files);

				fileSystem.listFiles(*files, path);

				message->setResults(files);
				message->markHandled();
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