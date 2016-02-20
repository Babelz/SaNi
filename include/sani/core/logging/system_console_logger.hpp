#pragma once

#include "sani/forward_declare.hpp"
#include "sani/core/logging/logger.hpp"

SANI_FORWARD_DECLARE_ENUM_CLASS_2(sani, console, ConsoleColor);

namespace sani {

	/// @class SystemConsoleLogger system_console_logger.hpp "sani/core/logging/system_console_logger.hpp"
	/// @author voidbab
	/// 
	/// Logger that can log to the system console.
	/// It will custom format the messages and color them
	/// depending on the log level.
	class SystemConsoleLogger final : public Logger<SystemConsoleLogger> {
	private:
		void internalLog(const String& from, const String& message, const LogLevel level, const console::ConsoleColor color) const;
	public:
		SystemConsoleLogger();

		void logError(const String& from, const String& message);
		void logWarning(const String& from, const String& message);
		void logInfo(const String& from, const String& message);
		
		~SystemConsoleLogger() = default;
	};
}