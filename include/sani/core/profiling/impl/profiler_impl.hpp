#pragma once

#include "sani/core/profiling/profiler_module.hpp"
#include "sani/core/profiling/profiler_entry.hpp"
#include <unordered_map>

namespace sani {
	
	namespace profiler {

		using Modules = std::unordered_map<String, ProfilerModule>;

		/// @class ProfilerImpl profiler_impl.hpp "sani/core/profiling/impl/profiler_impl.hpp"
		/// @author voidbab
		///
		/// Contains implementation for the profiler.
		struct ProfilerImpl final {
			Modules modules;
			
			ProfilerEntry root;
			String rootFunction;
			String rootModule;
			
			ProfilerImpl();
			
			~ProfilerImpl() = default;
		};
	}
}