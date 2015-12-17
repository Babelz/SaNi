#pragma once

#include "sani/forward_declare.hpp"
#include "sani/types.hpp"

SANI_FORWARD_DECLARE_3(sani, engine, messages, QueryMessage);

namespace sani {

	namespace engine {
		
		namespace services {
			
			/// ! Contains the contract definition and helper functions to interact with 
			///   the file system service.
			namespace filesystemservice {

				/*
					TODO: add definition.
				*/

				enum class FilesystemServiceCommands : uint32 {
					FileExists			= 0,

					OpenFile			= 1,

					CloseFile			= 2,

					IsAbsolutePath		= 3,

					GetFileData			= 4,

					GetFileDataString	= 5,

					ListFiles			= 6,

					GetFileData			= 7
				};

				/*
					TODO: comment.
				*/

				void fileExists(messages::QueryMessage* const message);
				
				void openFile(messages::QueryMessage* const message);

				void closeFile(messages::QueryMessage* const message);
				
				void isAbsolutePath(messages::QueryMessage* const message);
				
				void getFileDataString(messages::QueryMessage* const message);

				void listFiles(messages::QueryMessage* const message);

				void getFileData(messages::QueryMessage* const message);
			}
		}
	}
}