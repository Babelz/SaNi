#include "sani/core/profiling/profiler_module.hpp"
#include "sani/core/profiling/profiler.hpp"
#include "sani/debug.hpp"

namespace sani {

	namespace profiler {

		void startProfiler(const String& module, const String& function) {
			impl.root.beginProfiling(function);
		}
		void stopProfiler(const String& module, const String& function) {
			impl.root.beginProfiling(function);
		}

		void startProfiling(const String& module, const String& function) {
			SANI_ASSERT(impl.rootModule == module);
			SANI_ASSERT(impl.rootFunction == module);

			impl.modules[module].beginProfiling(function);
		}
		void endProfiling(const String& module, const String& function) {
			impl.modules[module].endProfiling(function);
		}

		void createRoot(const String& module, const String& function) {
			impl.rootModule		= module;
			impl.rootFunction	= function;
		}
	}
}