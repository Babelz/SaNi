#include "sani/engine/mono/mono_define.hpp"

#include "sani/engine/mono/mono_runtime.hpp"
#include "sani/engine/mono/mono_provider.hpp"
#include "sani/engine/mono/glib_types.hpp"
#include "sani/engine/mono/services_mono.hpp"
#include "sani/core/logging/log.hpp"

#include "sani/engine/sani_engine.hpp"
#include "mono/metadata/object.h"

namespace sani {

	namespace engine {

		MONO_MODULE_IMPL(services)

		static void MONO_FUNCTION_IMPL(InternalCreateService)(MonoString* name, gint32* id) {
		};

		static void MONO_FUNCTION_IMPL(Start)(MonoString* inst) {
		};

		static void MONO_FUNCTION_IMPL(Suspend)(MonoString* inst) {
		};

		static void MONO_FUNCTION_IMPL(Terminate)(MonoString* inst) {
		};

		MONO_MODULE_INITIALIZER {
			MONO_DEFINE_CLASS(SaNi.Mono.Services, EngineService);

			MONO_DEFINE_FUNCTION(InternalCreateService, (string, ref int));
			MONO_DEFINE_FUNCTION(Start, MonoString*);
			MONO_DEFINE_FUNCTION(Suspend, MonoString*);
			MONO_DEFINE_FUNCTION(Terminate, MonoString*);
		};

		MONO_MODULE_IMPL_END
	}
}