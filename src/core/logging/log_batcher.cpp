#include "sani/core/logging/log_level.hpp"
#include "sani/core/logging/logging_helpers.hpp"
#include "sani/core/logging/log_batcher.hpp"
#include "sani/debug.hpp"

namespace sani {

	/*
		BatchEntry members.
	*/

	LogBatchEntry::LogBatchEntry(const String& line, const LogLevel level) : line(line), level(level) {
	}
	LogBatchEntry::LogBatchEntry() {
	}

	/*
		LogBatchResults members.
	*/

	LogBatch::LogBatch(const String& from, const String& name, const String& log)
		: from(from), name(name) {
	}
	LogBatch::LogBatch() {
	}

	/*
		LogBatch members.
	*/

	void LogBatcher::beginLog(const String& from, const String& name) {
		SANI_ASSERT(!from.empty());

		data.from = from;
		data.name = name;

		data.log.clear();

		data.log.push_back(LogBatchEntry(name + " - BATCH BEG ->", LogLevel::Info));
	}

	void LogBatcher::logError(const String& message) {
		String formatted = message;

		formatError(data.from, formatted);

		data.log.push_back(LogBatchEntry(formatted, LogLevel::Error));
	}
	void LogBatcher::logWarning(const String& message) {
		String formatted = message;

		formatWarning(data.from, formatted);

		data.log.push_back(LogBatchEntry(formatted, LogLevel::Warning));
	}
	void LogBatcher::logInfo(const String& message) {
		String formatted = message;

		formatInfo(data.from, formatted);

		data.log.push_back(LogBatchEntry(formatted, LogLevel::Info));
	}

	void LogBatcher::incrementScope() {
	}
	void LogBatcher::decrementScope() {
	}
}