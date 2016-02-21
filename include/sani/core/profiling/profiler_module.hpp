#pragma once

#include "sani/core/profiling/profiler_entry.hpp"
#include "sani/types.hpp"

#include <unordered_map>
#include <iterator>

namespace sani {

	using ProfilerEntries = std::unordered_map<String, ProfilerEntry>;
	using ProfilerEntriesIterator = ProfilerEntries::const_iterator;

	/// @class ProfilerModule profiler_module.hpp "sani/core/profiling/profiler_module.hpp"
	/// @author voidbab
	/// 
	/// Single profiler module that is linked to the file name
	/// and contains all the functions that are being profiled
	/// in that file.
	class ProfilerModule final {
	private:
		std::unordered_map<String, ProfilerEntry> entries;
	public:
		ProfilerModule() = default;
		
		/// Returns the elapsed time it took for this module to run.
		float32 elapsedMicroSeconds() const;

		/// Begins profiling given function.
		void beginProfiling(const String& function);
		/// End profiling given function.
		void endProfiling(const String& function);
		
		ProfilerEntriesIterator begin() const;
		ProfilerEntriesIterator end() const;

		~ProfilerModule() = default;
	};
}