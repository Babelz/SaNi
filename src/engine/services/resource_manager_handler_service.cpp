#include "sani/engine/services/resource_manager_handler_service.hpp"
#include "sani/resource/resource_manager.hpp"
#include "sani/engine/messaging/messages/document_message.hpp"
#include "sani/engine/sani_engine.hpp"

#include "sani/engine/services/cvar_service.hpp"
#include "sani/engine/services/contracts/cvar_service_contract.hpp"
#include "sani/engine/services/contracts/resource_manager_handler_contract.hpp"
#include "sani/engine/services/render_service.hpp"
#include "sani/engine/services/contracts/render_service_contract.hpp"
#include "sani/platform/graphics/graphics_device.hpp"

namespace sani {

	namespace engine {
		
		namespace services {

			using namespace sani::engine::services::resourcemanagerhandler;

			ResourceManagerHandlerService::ResourceManagerHandlerService(SaNiEngine* const engine) : EngineService("resource manager handler", engine) {
			}

			void ResourceManagerHandlerService::handleDocumentMessage(messages::DocumentMessage* const message) {
				const ResourceManagerHandlerCommands command = static_cast<ResourceManagerHandlerCommands>(message->getCommand());

				if (command == ResourceManagerHandlerCommands::GetDefaultResourceManager) getDefaultManager(message);
			}

			void ResourceManagerHandlerService::createDefaultManager() {
				SaNiEngine* engine = getEngine();

				auto* listCVars = engine->createEmptyMessage<messages::DocumentMessage>();
				cvarservice::listCVars(listCVars);
				engine->routeMessage(listCVars);

				auto* cvars = static_cast<std::vector<CVar* const>*>(listCVars->getData());

				String contentRoot;
				FIND_VAR_OR_DEFAULT(cvars, "content_root", contentRoot, "../../assets/");
				
				auto* getDevice = engine->createEmptyMessage<messages::DocumentMessage>();
				renderservice::getGraphicsDevice(getDevice);
				engine->routeMessage(getDevice);

				auto* device = static_cast<sani::graphics::GraphicsDevice*>(getDevice->getData());

				managers.push_back(new sani::resource::ResourceManager(&fileSystem, device, engine, contentRoot));

				engine->deallocateShared(cvars);
				engine->releaseMessage(listCVars);
				engine->releaseMessage(getDevice);
			}

			void ResourceManagerHandlerService::getDefaultManager(messages::DocumentMessage* const message)  {
				message->setData(managers[0]);
				message->markHandled();
			}
			bool ResourceManagerHandlerService::onStart() {
				createDefaultManager();

				return true;
			}
	
			void ResourceManagerHandlerService::receive(messages::Message* const message) {
				const MessageType type = static_cast<MessageType>(message->getType());

				if (type == MessageType::Document) handleDocumentMessage(static_cast<messages::DocumentMessage*>(message));
			}
		}
	}
}