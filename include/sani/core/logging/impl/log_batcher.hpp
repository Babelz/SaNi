#pragma once

#include "sani/core/utils/string_utils.hpp"

namespace sani {
	
	using namespace utils;

	template<class T>
	void LogBatcher::log(T& logger) {
		for (auto logEntry : _log) {
			const String entryIdent	= repeat(ident, logEntry.scope);
			const String line		= entryIdent + logEntry.line;

			switch (logEntry.level) {
			case LogLevel::Error:
				logger.logError(from, line);
				break;
			case LogLevel::Warning:
				logger.logWarning(from, line);
				break;
			case LogLevel::Info:
				logger.logInfo(from, line);
				break;
			default:
				break;
			}
		}

		logger.logInfo(from, name + " - BATCH END");
	}
}