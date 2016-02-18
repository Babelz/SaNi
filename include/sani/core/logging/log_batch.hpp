#pragma once

#include "sani/types.hpp"
#include <vector>

namespace sani {

	struct LogBatchResults final {
		const String from;
		const String name;

		const String log;

		LogBatchResults(const String& from, const String& name, const String& log);

		~LogBatchResults() = default;
	};

	class LogBatch final {
	private:
		String from;
		String name;
		
		String log;
	public:
		LogBatch() = default;

		void beginLog(String& from, String& name);

		void logError(String& message);
		void logWarning(String& message);
		void logInfo(String& message);

		void endLog(String& endMessage);
		
		void results(LogBatchResults& results);

		~LogBatch() = default;
	};
}