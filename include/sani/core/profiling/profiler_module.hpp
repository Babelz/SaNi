#pragma 

#include "sani/core/profiling/profiler_entry.hpp"
#include "sani/types.hpp"

#include <unordered_map>
#include <iterator>

namespace sani {

	using ProfilerEntries = std::unordered_map<String, ProfilerEntry>;
	using ProfilerEntriesIterator = ProfilerEntries::const_iterator;

	class ProfilerModule final {
	private:
		std::unordered_map<String, ProfilerEntry> entries;
		
		const String fileName;
	public:
		ProfilerModule(const String& fileName);
		
		const String& getFileName() const;

		Time moduleAverageTime(const Time& rootTime);
		Time moduleTime() const;

		void beginProfiling(const String& function);
		void endProfiling(const String& function);
		
		ProfilerEntriesIterator begin() const;
		ProfilerEntriesIterator end() const;

		~ProfilerModule() = default;
	};
}