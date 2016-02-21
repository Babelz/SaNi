#pragma endregion

#include "sani/platform/time/time.hpp"
#include "sani/types.hpp"

namespace sani {

	class ProfilerSample final {
	private:
		Time start;
		Time end;
	public:
		ProfilerSample();

		Time getElapsedTime() const;

		void start();
		void end();

		~ProfilerSample() = default;
	};
}