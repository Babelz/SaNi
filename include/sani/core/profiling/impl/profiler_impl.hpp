#pragma once

#include "sani/core/profiling/profiler_module.hpp"
#include <unordered_map>

namespace sani {
	
	namespace profiler {

		/// @class ProfilerImpl profiler_impl.hpp "sani/core/profiling/impl/profiler_impl.hpp"
		/// @author voidbab
		///
		/// Contains implementation for the profiler.
		struct ProfilerImpl final {
			std::unordered_map<String, ProfilerModule> modules;
			
			ProfilerModule root;
			String rootFunction;
			String rootModule;
			
			ProfilerImpl();
			
			~ProfilerImpl() = default;
		};
	}
}