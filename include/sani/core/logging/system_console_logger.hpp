#pragma once

#include "sani/core/logging/logger.hpp"

namespace sani {

	class SystemConsoleLogger final : public Logger<SystemConsoleLogger> {
	private:
		void logError(const String& from, const String& message);
		void logWarning(const String& from, const String& message);
		void logInfo(const String& from, const String& message);
	public:
		SystemConsoleLogger();

		~SystemConsoleLogger();
	};
}