#include "sani/engine/mono/mono_define.hpp"

#include "sani/engine/mono/mono_runtime.hpp"
#include "sani/engine/mono/mono_provider.hpp"
#include "sani/engine/mono/glib_types.hpp"
#include "sani/engine/mono/services_mono.hpp"
#include "sani/core/logging/log.hpp"

#include "sani/engine/sani_engine.hpp"
#include "mono/metadata/object.h"

#include "sani/engine/services/contracts/cvar_service_contract.hpp"
#include "sani/engine/messaging/messages/document_message.hpp"
#include "sani/core/cvar/cvar.hpp"

#include "sani/core/utils/string_utils.hpp"

namespace sani {

	namespace engine {

		MONO_MODULE_IMPL(services)

		static void findUserServices(std::vector<String>& userServiceTypeNames) {
			auto* message = engine->createEmptyMessage<messages::DocumentMessage>();
			cvarservice::listCVars(message);
			engine->routeMessage(message);

			auto cvars = static_cast<std::vector<CVar* const>*>(message->getData());
			
			String userServices;
			FIND_VAR_OR_DEFAULT(cvars, "user_services", userServices, "");

			// No user services found, return.
			if (userServices.empty()) return;

			// Split and parse.
			utils::split(userServices, ",", userServiceTypeNames, true);

			engine->releaseMessage(message);
			engine->deallocateShared(cvars);
		}

		static void InternalCreateService(MonoString* name) {
		};

		static void Start(MonoString* inst) {
		};

		static void Suspend(MonoString* inst) {
		};

		static void Terminate(MonoString* inst) {
		};

		static MonoString* InternalGetName(MonoString* inst) {
			return mono_string_new(MONO_DOMAIN, "asd");
		}
		static gint32 InternalGetID(MonoString* inst) {
			return 0;
		}
		static gint32 InternalGetState(MonoString* inst) {
			return 0;
		}

		bool initialize() {
			std::vector<String> userServiceTypeNames;
			findUserServices(userServiceTypeNames);

			if (userServiceTypeNames.empty()) {
				FNCLOG_INF(log::OutFlags::All, "no user defined services found in configuration, skipping...");

				return true;
			}

			// Hook base class methods.
			MONO_REGISTER_KNOWN_FUNCTION(SaNi.Mono.Services, EngineService, InternalGetName, NO_ARGS, InternalGetName);
			MONO_REGISTER_KNOWN_FUNCTION(SaNi.Mono.Services, EngineService, InternalGetID, NO_ARGS, InternalGetID);
			MONO_REGISTER_KNOWN_FUNCTION(SaNi.Mono.Services, EngineService, InternalGetState, NO_ARGS, InternalGetState);
			MONO_REGISTER_KNOWN_FUNCTION(SaNi.Mono.Services, EngineService, InternalCreateService, (MonoString* name), InternalCreateService);
			MONO_REGISTER_KNOWN_FUNCTION(SaNi.Mono.Services, EngineService, Start, NO_ARGS, Start);
			MONO_REGISTER_KNOWN_FUNCTION(SaNi.Mono.Services, EngineService, Suspend, NO_ARGS, Suspend);
			MONO_REGISTER_KNOWN_FUNCTION(SaNi.Mono.Services, EngineService, Terminate, NO_ARGS, Terminate);

			for (auto& userServiceTypeName : userServiceTypeNames) {
				//MONO_DEFINE_CLASS(SaNi.Mono.Services, EngineService); 

				//MONO_REGISTER_FUNCTION(InternalCreateService, EngineService);
				//MONO_REGISTER_FUNCTION(Start, EngineService);
				//MONO_REGISTER_FUNCTION(Suspend, EngineService);
				//MONO_REGISTER_FUNCTION(Terminate, EngineService);

				// Mono namespace.
				const String ns = userServiceTypeName.substr(0, userServiceTypeName.find_last_of("."));
				// Mono class name.
				const String cn = userServiceTypeName.substr(userServiceTypeName.find_last_of(".") + 1);

				const MonoClassDefinition classDef(ns.c_str(), cn.c_str());

				if (MONO_PROVIDER->classExists(&classDef)) {
				
				}
			}

			return true;
		}

		MONO_MODULE_IMPL_END
	}
}