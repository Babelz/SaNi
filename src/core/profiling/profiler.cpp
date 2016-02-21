#include "sani/core/profiling/profiler_module.hpp"
#include "sani/core/profiling/profiler.hpp"
#include "sani/debug.hpp"

namespace sani {

	namespace profiler {

		namespace __privns__ {

			void startProfiler(const String& module, const String& function) {
				SANI_ASSERT(impl.rootModule == module);
				SANI_ASSERT(impl.rootFunction == function);

				impl.root.beginMeasure();
			}
			void stopProfiler(const String& module, const String& function) {
				impl.root.endMeasure();
			}

			void startProfiling(const String& module, const String& function) {
				impl.modules[module].beginProfiling(function);
			}
			void endProfiling(const String& module, const String& function) {
				impl.modules[module].endProfiling(function);
			}

			void makeRoot(const String& module, const String& function) {
				impl.rootModule = module;
				impl.rootFunction = function;
			}
		}

		float32 rootElapsedMicroseconds() {
			return impl.root.averageMicroSeconds();
		}
		const String& rootFunction() {
			return impl.rootFunction;
		}
		const String& rootModule() {
			return impl.rootModule;
		}

		const Modules& modules() {
			return impl.modules;
		}
	}
}