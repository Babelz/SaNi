#pragma once

#include "sani/core/profiling/impl/profiler_impl.hpp"

#include <list>

#define BEGIN_PROFILING		sani::profiler::startProfiling(__FILE__, __FUNCTION__)
#define END_PROFILING		sani::profiler::endProfiling(__FILE__, __FUNCTION__)

#define START_PROFILER		sani::profiler::startProfiler(__FILE__, __FUNCTION__)
#define STOP_PROFILER		sani::profiler::stopProfiler(__FILE__, __FUNCTION__)

#define PROFILER_MAKE_ROOT	sani::profiler::makeRoot(__FILE__, __FUNCTION__)

namespace sani {

	namespace profiler {

		namespace {
			ProfilerImpl impl;
		}

		void startProfiler(const String& module, const String& function);
		void stopProfiler(const String& module, const String& function);

		void startProfiling(const String& module, const String& function);
		void endProfiling(const String& module, const String& function);

		void makeRoot(const String& module, const String& function);
	}
}