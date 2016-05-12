#include "sani/engine/mono/mono_include.hpp"
#include "sani/engine/mono/mono_define.hpp"

#include "sani/engine/services/contracts/cvar_service_contract.hpp"
#include "sani/engine/messaging/messages/document_message.hpp"
#include "sani/core/cvar/cvar.hpp"

#include "sani/core/utils/string_utils.hpp"

#include "sani/engine/services/user_service.hpp"

namespace sani {

	namespace engine {

		/*
			TODO: cleanup.
		*/

		MONO_MODULE_IMPL(services)

		/*
			Utils.
		*/

		// Find all user services listed in configuration that the user
		// wants to use for this application.
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

		/*
			CIL internal call impls.
		*/

		static void Instantiate(MonoObject* instance, MonoString* name, uint32* ptr) {
			// Create and store.
			UserService* service = new UserService(instance, name, engine);

			// Pin our service, else it gets collected by the gc.
			MONO_PROVIDER->pin(instance);

			*ptr = reinterpret_cast<IntPtr>(service);
		}

		static MonoBoolean Start(MonoObject* instance) {
			return getInstance<UserService>(instance)->start();
		}

		static void Suspend(MonoObject* instance) {
			getInstance<UserService>(instance)->suspend();
		}

		static void Terminate(MonoObject* instance) {
			UserService* const service = getInstance<UserService>(instance);

			service->terminate();

			delete service;
		}

		static MonoString* InternalGetName(MonoObject* instance) {
			return MONO_PROVIDER->createString(getInstance<UserService>(instance)->getName().c_str());
		}
		static int32 InternalGetID(MonoObject* instance) {
			return getInstance<UserService>(instance)->getID();
		}
		static int32 InternalGetState(MonoObject* instance) {
			return static_cast<int32>(getInstance<UserService>(instance)->getState());
		}

		static void registerKnownFunctions() {
			MONO_REGISTER_KNOWN_FUNCTION(SaNi.Mono.Services, EngineService, InternalGetName, InternalGetName);
			MONO_REGISTER_KNOWN_FUNCTION(SaNi.Mono.Services, EngineService, InternalGetID, InternalGetID);
			MONO_REGISTER_KNOWN_FUNCTION(SaNi.Mono.Services, EngineService, InternalGetState, InternalGetState);
			MONO_REGISTER_KNOWN_FUNCTION(SaNi.Mono.Services, EngineService, Instantiate, Instantiate);
			MONO_REGISTER_KNOWN_FUNCTION(SaNi.Mono.Services, EngineService, Start, Start);
			MONO_REGISTER_KNOWN_FUNCTION(SaNi.Mono.Services, EngineService, Suspend, Suspend);
			MONO_REGISTER_KNOWN_FUNCTION(SaNi.Mono.Services, EngineService, Terminate, Terminate);
		}
		static void createUserService(const MonoClassDefinition* const classDef, const HookFlags flags) {
			MonoObject* instance = MONO_PROVIDER->createObject(classDef);

			UserService* service = getInstance<UserService>(instance);
			service->setMonoHooks(flags);

			if (!service->start()) {
				FNCLOG_ERR(log::OutFlags::All, "could not start service, not going to add to the engine...");

				delete service;
			}
			else {
				engine->registerService(service);
			}
		}

		bool initialize() {
			std::vector<String> userServiceTypeNames;
			findUserServices(userServiceTypeNames);

			if (userServiceTypeNames.empty()) {
				FNCLOG_INF(log::OutFlags::All, "no user defined services found in configuration, skipping...");

				return true;
			}

			registerKnownFunctions();

			// Hook function definitions.
			const MonoFunctionDefinition onStartDef("OnStart", nullptr);
			const MonoFunctionDefinition onResumeDef("OnResume", nullptr);
			const MonoFunctionDefinition onSuspendedDef("OnSuspended", nullptr);
			const MonoFunctionDefinition onTerminatedDef("OnTerminated", nullptr);
			const MonoFunctionDefinition onUpdateDef("OnUpdate", nullptr, 1);

			for (auto& userServiceTypeName : userServiceTypeNames) {
				// Mono namespace.
				const String ns = userServiceTypeName.substr(0, userServiceTypeName.find_last_of("."));
				// Mono class name.
				const String cn = userServiceTypeName.substr(userServiceTypeName.find_last_of(".") + 1);

				const MonoClassDefinition classDef(ns.c_str(), cn.c_str());

				if (MONO_PROVIDER->classExists(&classDef)) {
					// Found class.
					// Lookup for hooks.
					HookFlags flags = HookFlags::None;

					if (MONO_PROVIDER->functionExists(&classDef, &onStartDef))		flags |= HookFlags::OnStart;
					if (MONO_PROVIDER->functionExists(&classDef, &onResumeDef))		flags |= HookFlags::OnResume;
					if (MONO_PROVIDER->functionExists(&classDef, &onSuspendedDef))	flags |= HookFlags::OnSuspended;
					if (MONO_PROVIDER->functionExists(&classDef, &onTerminatedDef)) flags |= HookFlags::OnTerminated;
					if (MONO_PROVIDER->functionExists(&classDef, &onUpdateDef))		flags |= HookFlags::OnUpdate;
					
					createUserService(&classDef, flags);
				} else {
					FNCLOG_ERR(log::OutFlags::All, "could not find service named " + cn);

					continue;
				}
			}

			return true;
		}

		MONO_MODULE_IMPL_END
	}
}