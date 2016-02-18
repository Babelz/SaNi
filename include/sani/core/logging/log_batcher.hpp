#pragma once

#include "sani/forward_declare.hpp"
#include "sani/core/logging/log_level.hpp"
#include "sani/forward_declare.hpp"
#include "sani/types.hpp"
#include <list>

namespace sani {

	struct LogBatchEntry final {
		String line;
		LogLevel level;
		uint32 scope;

		LogBatchEntry(const String& line, const LogLevel level);
		LogBatchEntry();

		~LogBatchEntry() = default;
	};

	struct LogBatch final {
		String from;
		String name;

		std::list<LogBatchEntry> log;

		LogBatch(const String& from, const String& name, const String& log);
		LogBatch();

		~LogBatch() = default;
	};

	class LogBatcher final {
	private:
		LogBatch data;

		uint32 scope;
	public:
		LogBatcher() = default;

		void beginLog(const String& from, const String& name);

		void logError(const String& message);
		void logWarning(const String& message);
		void logInfo(const String& message);

		void incrementScope();
		void decrementScope();

		template<class T>
		void endLog(T& logger);

		~LogBatcher() = default;
	};
}

#include "sani/core/logging/impl/log_batcher.hpp"