#pragma once

#include "sani/engine/services/engine_service.hpp"
#include "sani/platform/file/file_system.hpp"
#include "sani/forward_declare.hpp"

SANI_FORWARD_DECLARE_3(sani, engine, messages, CommandMessage);
SANI_FORWARD_DECLARE_3(sani, engine, messages, QueryMessage);
SANI_FORWARD_DECLARE_2(sani, engine, SaniEngine);

namespace sani {

	namespace engine {
		
		namespace services {

			class FileSystemService : public EngineService {
			private:	
				io::FileSystem fileSystem;

				void handleQueryMessage(messages::QueryMessage* const message);
				void handleCommandMessage(messages::CommandMessage* const message);

				void fileExists(messages::QueryMessage* const message);
				void openFile(messages::QueryMessage* const message);
				void closeFile(messages::CommandMessage* const message);

				void isAbsolutePath(messages::QueryMessage* const message);
				
				void getFileData(messages::QueryMessage* const message);
				void getFileDataString(messages::QueryMessage* const message);
				
				void listFiles(messages::QueryMessage* const message);
			public:
				FileSystemService(SaNiEngine* const engine);

				void receive(messages::Message* const message) final override;
			};
		}
	}
}