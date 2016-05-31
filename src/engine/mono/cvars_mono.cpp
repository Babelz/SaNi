#include "sani/engine/mono/cvars_mono.hpp"
#include "sani/engine/mono/mono_define.hpp"

#include "sani/engine/services/contracts/cvar_service_contract.hpp"
#include "sani/engine/messaging/messages/document_message.hpp"

#include "sani/core/cvar/cvar.hpp"

#include "sani/engine/mono/mono_define.hpp"

#include <vector>

namespace sani {

	namespace engine {

		MONO_MODULE_IMPL(cvars)

		/*
			CVar.cs members
		*/

		static void ReadString(MonoObject* instance, MonoString** value) {
			CVar* cvar = getInstance<CVar>(instance);

			String str;
			cvar->read(str);

			*value = MONO_PROVIDER->createString(str.c_str());
		}
		static void ReadInt(MonoObject* instance, int32* value) {
			CVar* cvar = getInstance<CVar>(instance);

			int32 ival;
			cvar->read(ival);

			*value = ival;
		}
		static void ReadFloat(MonoObject* instance, float32* value) {
			CVar* cvar = getInstance<CVar>(instance);

			float32 fval;
			cvar->read(fval);

			*value = fval;
		}
		static void ReadDouble(MonoObject* instance, float64* value) {
			CVar* cvar = getInstance<CVar>(instance);

			float64 fval;
			cvar->read(fval);

			*value = fval;
		}

		static bool InternalWrite(MonoObject* instance, MonoObject** value, MonoString* typeName) {
			CVar* cvar = getInstance<CVar>(instance);

			if (!cvar->canWrite()) return false;

			const String str = String(mono_string_to_utf8(typeName));

			if (str == "int") {
				int32 ival = *MONO_UNBOX(*value, int32);
				
				cvar->write(ival);
			}
			if (str == "float") {
				float32 fval = *MONO_UNBOX(*value, float32);

				cvar->write(fval);
			}
			if (str == "double") {
				float64 fval = *MONO_UNBOX(*value, float64);

				cvar->write(fval);
			}
			if (str == "string") {
				const auto str = String(mono_string_to_utf8(MONO_UNBOX(*value, MonoString)));

				cvar->write(str);
			}

			return true;
		}

		static void GetValueType(MonoObject* instance, int8* value) {
			CVar* cvar = getInstance<CVar>(instance);

			*value = static_cast<int8>(cvar->getType());
		}
		static void GetName(MonoObject* instance, MonoString** value) {
			CVar* cvar = getInstance<CVar>(instance);
			
			*value = MONO_PROVIDER->createString(cvar->getName().c_str());
		}
		static void GetCanWrite(MonoObject* instance, bool* value) {
			CVar* cvar = getInstance<CVar>(instance);

			*value = cvar->canWrite();
		}
		static void GetHasChanged(MonoObject* instance, bool* value) {
			CVar* cvar = getInstance<CVar>(instance);

			*value = cvar->hasChanged();
		}
		static void GetIsSynced(MonoObject* instance, bool* value) {
			CVar* cvar = getInstance<CVar>(instance);
			
			*value = cvar->isSynced();
		}

		/*
			CVars.cs members
		*/

		static void GetNativeCVars(std::vector<CVar*>& results) {
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

		static MonoArray* GetCVars() {
			std::vector<CVar*> cvars;

			GetNativeCVars(cvars);

			const MonoClassDefinition classDef("SaNi.Mono.Configuration", "CVar");

			MonoArray* results = MONO_PROVIDER->createArray(&classDef, cvars.size());

			// Get handles, create wrappers.
			for (uint32 i = 0; i < cvars.size(); i++) {
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

		bool initialize() {
			MONO_REGISTER_KNOWN_FUNCTION(SaNi.Mono.Configuration, CVar, GetValueType, GetValueType);
			MONO_REGISTER_KNOWN_FUNCTION(SaNi.Mono.Configuration, CVar, GetName, GetName);
			MONO_REGISTER_KNOWN_FUNCTION(SaNi.Mono.Configuration, CVar, GetCanWrite, GetCanWrite);
			MONO_REGISTER_KNOWN_FUNCTION(SaNi.Mono.Configuration, CVar, GetHasChanged, GetHasChanged);
			MONO_REGISTER_KNOWN_FUNCTION(SaNi.Mono.Configuration, CVar, ReadString, ReadString);
			MONO_REGISTER_KNOWN_FUNCTION(SaNi.Mono.Configuration, CVar, ReadInt, ReadInt);
			MONO_REGISTER_KNOWN_FUNCTION(SaNi.Mono.Configuration, CVar, ReadFloat, ReadFloat);
			MONO_REGISTER_KNOWN_FUNCTION(SaNi.Mono.Configuration, CVar, ReadDouble, ReadDouble);

			MONO_REGISTER_KNOWN_FUNCTION(SaNi.Mono.Configuration, CVars, GetCVars, GetCVars);
			
			return true;
		}

		MONO_MODULE_IMPL_END
	}
}