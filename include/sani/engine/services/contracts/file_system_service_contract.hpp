#pragma once

#include "sani/engine/messaging/messages/document_message.hpp"
#include "sani/types.hpp"

namespace sani {

	namespace engine {
		
		namespace services {
			
			/// ! Contains the contract definition and helper functions to interact with 
			///   the file system service.
			namespace filesystemservice {

				/*
					TODO: add definition.
				*/

				enum class FilesystemCommands : uint32 {
					FileExists			= 0,

					OpenFile			= 1,

					CloseFile			= 2,

					IsAbsolutePath		= 3,

					GetFileData			= 4,

					GetFileDataString	= 5,

					ListFiles			= 6
				};

				/*
					TODO: comment.
				*/

				void fileExists(messages::DocumentMessage* const message);
				
				void openFile(messages::DocumentMessage* const message);

				void closeFile(messages::DocumentMessage* const message);
				
				void isAbsolutePath(messages::DocumentMessage* const message);
				
				void getFileDataString(messages::DocumentMessage* const message);
				
				void listFiles(messages::DocumentMessage* const message);
			}
		}
	}
}