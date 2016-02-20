#pragma once

#include "sani/core/utils/string_utils.hpp"

namespace sani {
	
	using namespace utils;

	template<class T>
	void LogBatcher::log(T& logger) const {
		for (auto logEntry : entries) {
			const String logIdent = repeat(ident, logEntry.scope);
			const String logLine  = logIdent + logEntry.line;

			switch (logEntry.level) {
			case LogLevel::Error:
				logger.logError(from, logLine);
				break;
			case LogLevel::Warning:
				logger.logWarning(from, logLine);
				break;
			case LogLevel::Info:
				logger.logInfo(from, logLine);
				break;
			default:
				break;
			}
		}
	}
}