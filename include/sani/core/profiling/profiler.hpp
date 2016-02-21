#pragma once

#include "sani/core/profiling/impl/profiler_impl.hpp"
#include "sani/core/profiling/profiler_module.hpp"
#include "sani/core/utils/string_utils.hpp"

#include <list>

#define BEGIN_PROFILING		sani::profiler::__privns__::startProfiling(typeid(this).name(), __FUNCTION__)
#define END_PROFILING		sani::profiler::__privns__::endProfiling(typeid(this).name(), __FUNCTION__)

#define START_PROFILER		sani::profiler::__privns__::startProfiler(typeid(this).name(), __FUNCTION__)
#define STOP_PROFILER		sani::profiler::__privns__::stopProfiler(typeid(this).name(), __FUNCTION__)

#define PROFILER_MAKE_ROOT	sani::profiler::__privns__::makeRoot(typeid(this).name(), __FUNCTION__)

namespace sani {

	namespace profiler {

		namespace {
			
			ProfilerImpl impl;
		}

		/*
			TODO: should these be "hidden" or not?..
		*/

		namespace __privns__ {
			
			void startProfiler(const String& module, const String& function);
			void stopProfiler(const String& module, const String& function);

			void startProfiling(const String& module, const String& function);
			void endProfiling(const String& module, const String& function);

			void makeRoot(const String& module, const String& function);
		}
		
		float32 rootElapsedMicroseconds();
		const String& rootFunction();
		const String& rootModule();

		const Modules& modules();
	}
}