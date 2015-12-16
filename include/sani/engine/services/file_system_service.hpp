#pragma once

#include "sani/engine/services/engine_service.hpp"
#include "sani/platform/file/file_system.hpp"
#include "sani/forward_declare.hpp"

SANI_FORWARD_DECLARE_3(sani, engine, messages, DocumentMessage);
SANI_FORWARD_DECLARE_2(sani, engine, SaniEngine);

namespace sani {

	namespace engine {
		
		namespace services {

			class FileSystemService : public EngineService {
			private:	
				sani::io::FileSystem fileSystem;

				void handleDocumentMessage(messages::DocumentMessage* const message);
			
				
			protected:
				void handleStateMessage(StateMessage* const message) final override;
			public:
				FileSystemService(SaNiEngine* const engine);

				void receive(messages::Message* const message) final override;
				void update(const EngineTime& time) final override;
			};
		}
	}
}