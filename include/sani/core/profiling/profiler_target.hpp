#pragma 

#include "sani/core/profiling/profiler_entry.hpp"
#include "sani/types.hpp"

#include <list>

namespace sani {

	class ProfilerEntryContainer final {
	private:
		std::list<ProfilerEntry> entries;
		
		String fileName;
	public:
		ProfilerEntryContainer();
		
		

		~ProfilerEntryContainer() = default;
	};
}