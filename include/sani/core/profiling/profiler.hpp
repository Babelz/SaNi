#pragma once

#include "sani/core/profiling/profiler_module.hpp"
#include "sani/forward_declare.hpp"

#include <list>

SANI_FORWARD_DECLARE_1(sani, ProfilerSample);

namespace sani {

	namespace profiler {

		namespace {
			std::list<ProfilerModule> modules;
			ProfilerSample* root;
		}


	}
}