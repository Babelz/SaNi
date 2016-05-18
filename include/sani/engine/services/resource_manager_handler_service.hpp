#pragma once

#include "sani/platform/file/file_system.hpp"
#include "sani/engine/services/engine_service.hpp"
#include "sani/forward_declare.hpp"

#include <vector>

SANI_FORWARD_DECLARE_2(sani, resource, ResourceManager);
SANI_FORWARD_DECLARE_3(sani, engine, messages, DocumentMessage);
SANI_FORWARD_DECLARE_2(sani, engine, SaNiEngine);

namespace sani {

	namespace engine {

		namespace services {

			using ManagerList = std::vector<sani::resource::ResourceManager*>;

			class ResourceManagerHandlerService final : public EngineService {
			private:
				io::FileSystem fileSystem;
				ManagerList managers;

				void handleDocumentMessage(messages::DocumentMessage* const message);

				void createDefaultManager();

				void getDefaultManager(messages::DocumentMessage* const message);
			protected:
				virtual bool onStart() final override;
			public:
				ResourceManagerHandlerService(SaNiEngine* const engine);
				
				virtual void receive(messages::Message* const message) final override;

				~ResourceManagerHandlerService() = default;
			};
		}
	}
}