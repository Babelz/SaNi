#pragma once

namespace sani {

	template<class T>
	void LogBatcher::endLog(T& logger) {
		for (auto logEntry : data.log) {
			switch (logEntry.level) {
			case LogLevel::Error:
				logger.logError(data.from, logEntry.line);
				break;
			case LogLevel::Warning:
				logger.logWarning(data.from, logEntry.line);
				break;
			case LogLevel::Info:
				logger.logInfo(data.from, logEntry.line);
				break;
			default:
				break;
			}
		}

		logger.logInfo(data.from, data.name + " - END");
	}
}