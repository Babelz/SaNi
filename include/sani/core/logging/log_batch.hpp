#pragma once

#include "sani/types.hpp"
#include <vector>

namespace sani {

	struct BatchLogResults final {
		const String from;
		const String name;

		const String log;

		BatchLogResults(const String& from, const String& name, const String& log);

		~BatchLogResults() = default;
	};

	class BatchLog final {
	private:
		String from;
		String name;
		
		String log;
	public:
		BatchLog() = default;

		void beginLog(String& from, String& name);

		void logError(String& message);
		void logWarning(String& message);
		void logInfo(String& message);

		void endLog(String& endMessage);
		
		void results(BatchLogResults& results);

		~BatchLog() = default;
	};
}