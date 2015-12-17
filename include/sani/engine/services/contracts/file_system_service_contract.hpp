#pragma once

#include "sani/platform/file/file_stream.hpp"
#include "sani/forward_declare.hpp"
#include "sani/types.hpp"

SANI_FORWARD_DECLARE_3(sani, engine, messages, CommandMessage);
SANI_FORWARD_DECLARE_3(sani, engine, messages, QueryMessage);
SANI_FORWARD_DECLARE_2(sani, io, FileStream);

namespace sani {

	namespace engine {
		
		namespace services {
			
			/// ! Contains the contract definition and helper functions to interact with 
			///   the file system service.
			namespace filesystemservice {

				/*
					File system service definition

					Purpose of the service: Provide a platform independent interface
											for the other services and the games to 
											work with files, directories and 
											file streams.
				*/

				enum class FilesystemServiceCommands : uint32 {
					FileExists			= 0,

					OpenFile			= 1,

					CloseFile			= 2,

					IsAbsolutePath		= 3,

					GetFileData			= 4,

					GetFileDataString	= 5,

					ListFiles			= 6
				};

				void fileExists(messages::QueryMessage* const message, const String& path);
				
				void openFile(messages::QueryMessage* const message, const String& path, const io::Filemode filemode);

				void closeFile(messages::CommandMessage* const message, const String& path);
				
				void isAbsolutePath(messages::QueryMessage* const message, const String& path);
				
				void getFileDataString(messages::QueryMessage* const message, const String& path);

				void listFiles(messages::QueryMessage* const message, const String& path);

				void getFileData(messages::QueryMessage* const message, const String& path);
			}
		}
	}
}