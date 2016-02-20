#include "sani/core/logging/log_level.hpp"
#include "sani/core/logging/logging_helpers.hpp"
#include "sani/core/logging/log_batcher.hpp"
#include "sani/debug.hpp"

namespace sani {

	/*
		BatchEntry members.
	*/

	LogBatchEntry::LogBatchEntry(const String& line, const LogLevel level, const uint32 scope) 
		: line(line), level(level), scope(scope) {
	}
	LogBatchEntry::LogBatchEntry(const String& line, const LogLevel level) 
		: LogBatchEntry(line, level, 0 ) {
	}
	LogBatchEntry::LogBatchEntry() {
	}

	/*
		LogBatch members.
	*/

	LogBatcher::LogBatcher() : scope(0),
							   ident("\t") {
	}

	const String& LogBatcher::getIdent() const {
		return ident;
	}
	void LogBatcher::setIdent(const String& ident) {
		this->ident = ident;
	}

	void LogBatcher::beginLog(const String& from, const String& name) {
		SANI_ASSERT(!from.empty());

		this->from	= from;
		this->name	= name;
		scope		= 0;

		entries.clear();

		entries.push_back(LogBatchEntry(name + " - BATCH BEG ->", LogLevel::Info));
	}

	void LogBatcher::logError(const String& message) {
		entries.push_back(LogBatchEntry(message, LogLevel::Error, scope));
	}
	void LogBatcher::logWarning(const String& message) {
		entries.push_back(LogBatchEntry(message, LogLevel::Warning, scope));
	}
	void LogBatcher::logInfo(const String& message) {
		entries.push_back(LogBatchEntry(message, LogLevel::Info, scope));
	}

	void LogBatcher::scopeStart() {
		scope++;
	}
	void LogBatcher::scopeEnd() {
		if (scope == 0) return;
		
		scope--;
	}
}