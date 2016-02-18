#pragma once

#include "sani/core/logging/logger.hpp"

namespace sani {

	class SystemConsoleLogger final : public Logger<SystemConsoleLogger> {
	public:
		SystemConsoleLogger();

		void logError(const String& from, const String& message);
		void logWarning(const String& from, const String& message);
		void logInfo(const String& from, const String& message);

		// Should the logger close the system console once it 
		// gets destroyed?
		~SystemConsoleLogger() = default;
	};
}