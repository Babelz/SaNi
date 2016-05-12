#include "sani/resource/resource_manager.hpp"
#include "sani/engine/messaging/messages/document_message.hpp"
#include "sani/engine/services/contracts/resource_manager_handler_contract.hpp"

#include "sani/engine/mono/resource_manager_mono.hpp"

#include "sani/engine/mono/texture2d_mono.hpp"
#include "sani/resource/texture2d.hpp"

#include "sani/engine/mono/mono_define.hpp"
#include "sani/engine/sani_engine.hpp"

#include <functional>
#include <unordered_map>

namespace sani {

	namespace engine {

		MONO_MODULE_IMPL(resourcemanager)

		using namespace sani::resource;

		using ContentLoader = std::function<MonoObject*(MonoString*)>;
		using ContentLoaderMappings = std::unordered_map<String, ContentLoader>;

		static ContentLoaderMappings mappings;
		static ResourceManager* resources;

		static void InternalLoad(MonoString* assetName, MonoString* typeName, MonoObject** asset) {
			const String cstr(mono_string_to_utf8(typeName));

			MonoObject* resource = nullptr;
			if (mappings.count(cstr)) resource = mappings[cstr](assetName);
		
			*asset = resource;
		}
		static void Unload() {
			resources->unload();
		}

		static MonoObject* loadTexture2D(MonoString* name) {
			const String cstr(mono_string_to_utf8(name));

			Texture2D* texture = resources->load<Texture2D>(cstr);
			
			MonoObject* textureMono = texture2dmonomodule::createTexture2D();
			texture2dmonomodule::registerTexture2D(texture, textureMono);
			
			return textureMono;
		}

		static void initializeLoaders() {
			mappings = ContentLoaderMappings {
				{ "Texture2D", loadTexture2D }
			};
		}
		static void getResourceManager() {
			auto* getDefaultManager = engine->createEmptyMessage<messages::DocumentMessage>();
			resourcemanagerhandler::getDefaultResourceManager(getDefaultManager);
			engine->routeMessage(getDefaultManager);

			resources = static_cast<ResourceManager*>(getDefaultManager->getData());

			engine->releaseMessage(getDefaultManager);
		}

		bool initialize() {
			initializeLoaders();
			getResourceManager();

			MONO_REGISTER_KNOWN_FUNCTION(SaNi.Mono.Resource, ResourceManager, InternalLoad, InternalLoad);
			MONO_REGISTER_KNOWN_FUNCTION(SaNi.Mono.Resource, ResourceManager, Unload, Unload);

			return resources != nullptr;
		}

		MONO_MODULE_IMPL_END
	}
}