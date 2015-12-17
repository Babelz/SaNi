#include "sani/engine/services/contracts/file_system_service_contract.hpp"

namespace sani {

	namespace engine {
		
		namespace services {
			
			namespace filesystemservice {

				static void decorateMessage(messages::DocumentMessage* const message, const FilesystemServiceCommands filesystemServiceCommands) {
					const uint32 command = static_cast<uint32>(filesystemServiceCommands);

					message->getRecipients().clear();
					message->getRecipients().addRecipient("file system service");

					message->setCommand(command);
				}

				void fileExists(messages::DocumentMessage* const message) {
					decorateMessage(message, FilesystemServiceCommands::FileExists);
				}

				void openFile(messages::DocumentMessage* const message) {
					decorateMessage(message, FilesystemServiceCommands::OpenFile);
				}

				void closeFile(messages::DocumentMessage* const message) {
					decorateMessage(message, FilesystemServiceCommands::CloseFile);
				}

				void isAbsolutePath(messages::DocumentMessage* const message) {
					decorateMessage(message, FilesystemServiceCommands::IsAbsolutePath);
				}

				void getFileDataString(messages::DocumentMessage* const message) {
					decorateMessage(message, FilesystemServiceCommands::GetFileDataString);
				}

				void listFiles(messages::DocumentMessage* const message) {
					decorateMessage(message, FilesystemServiceCommands::ListFiles);
				}

				void getFileData(messages::DocumentMessage* const message) {
					decorateMessage(message, FilesystemServiceCommands::GetFileData);
				}
			}
		}
	}
}