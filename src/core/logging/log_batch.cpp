#include "sani/core/logging/logging_helpers.hpp"
#include "sani/core/logging/log_batch.hpp"
#include "sani/debug.hpp"

namespace sani {

	/*
		LogBatchResults members.
	*/

	LogBatchData::LogBatchData(const String& from, const String& name, const String& log)
		: from(from), name(name) {
	}

	/*
		LogBatch members.
	*/

	void LogBatch::beginLog(const String& from, const String& name) {
		SANI_ASSERT(!from.empty());

		data.from = from;
		data.name = name;

		data.log.clear();

		data.log.push_back("[" + name + " (BATCH BEG)]->");
	}

	void LogBatch::logError(const String& message) {
		String formatted = message;

		formatError(data.from, formatted);

		data.log.push_back("\t" + formatted);
	}
	void LogBatch::logWarning(const String& message) {
		String formatted = message;

		formatWarning(data.from, formatted);

		data.log.push_back("\t" + formatted);
	}
	void LogBatch::logInfo(const String& message) {
		String formatted = message;

		formatInfo(data.from, formatted);

		data.log.push_back("\t" + formatted);
	}

	const LogBatchData& LogBatch::endLog() {
		data.log.push_back("[" + data.name + " (BATCH END)]");
		
		return data;
	}
}