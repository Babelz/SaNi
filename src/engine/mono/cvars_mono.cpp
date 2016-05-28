#include "sani/engine/mono/cvars_mono.hpp"
#include "sani/engine/mono/mono_define.hpp"

#include "sani/engine/services/contracts/cvar_service_contract.hpp"
#include "sani/engine/messaging/messages/document_message.hpp"

#include "sani/core/cvar/cvar.hpp"

#include <vector>

namespace sani {

	namespace engine {

		MONO_MODULE_IMPL(cvars)

		/*
			CVar.cs members
		*/

		static MonoObject* Read(MonoObject* instance) {
		}

		static bool Write(MonoObject* instance, MonoObject value) {
		}

		static void GetValueType(MonoObject* instance, int8 value) {
		}
		static void GetName(MonoObject* instance, MonoString* value) {
		}
		static void GetCanWrite(MonoObject* instance, bool* value) {
		}
		static void GetHasChanged(MonoObject* instance, bool* value) {
		}
		static void GetIsSynced(MonoObject* instance, bool* value) {
		}

		/*
			CVars.cs members
		*/

		static MonoArray* GetCVars() {
			std::vector<CVar*> cvars;

			GetCVars(cvars);

			const MonoClassDefinition classDef("SaNi.Mono.Configuration", "CVar");

			MonoArray* results = MONO_PROVIDER->createArray(&classDef, cvars.size());

			// Get handles, create wrappers.
			for (auto i = 0; i < cvars.size(); i++) {
				const uint32 argc = 1;

				IntPtr ptr = reinterpret_cast<IntPtr>(cvars[i]);

				void* args[argc] = {
					&ptr
				};

				MonoObject* cvar = MONO_PROVIDER->createObject(&classDef, args, argc);

				mono_array_set(results, MonoObject*, i, cvar);
			}

			return results;
		}

		/*
			No impl yet.

			TODO: impl.
		*/

		static MonoObject* Create(int8 valueType, MonoString* name, bool synced, MonoObject* value) {
			return nullptr;
		}

		static void GetCVars(std::vector<CVar*>& results) {
			auto* listCVars = engine->createEmptyMessage<messages::DocumentMessage>();
			cvarservice::listCVars(listCVars);

			// Route.
			engine->routeMessage(listCVars);

			// Get.
			auto* cvars = static_cast<std::vector<CVar* const>*>(listCVars->getData());

			// Copy.
			for (auto* cvar : *cvars) results.push_back(cvar);

			// Release.
			engine->deallocateShared(cvars);
			engine->releaseMessage(listCVars);
		}

		bool initialize() {
			return true;
		}

		MONO_MODULE_IMPL_END
	}
}