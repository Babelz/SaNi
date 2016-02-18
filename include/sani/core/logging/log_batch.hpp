#pragma once

#include "sani/types.hpp"
#include <list>

namespace sani {

	struct LogBatchData final {
		String from;
		String name;

		std::list<String> log;

		LogBatchData(const String& from, const String& name, const String& log);

		~LogBatchData() = default;
	};

	class LogBatch final {
	private:
		LogBatchData data;
	public:
		LogBatch() = default;

		void beginLog(const String& from, const String& name);

		void logError(const String& message);
		void logWarning(const String& message);
		void logInfo(const String& message);

		const LogBatchData& endLog();

		~LogBatch() = default;
	};
}