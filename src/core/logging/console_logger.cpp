#include "sani/core/logging/system_console_logger.hpp"
#include "sani/core/logging/logging_helpers.hpp"
#include "sani/platform/console.hpp"

namespace sani {

	SystemConsoleLogger::SystemConsoleLogger() : Logger<SystemConsoleLogger>("system console logger") {
		if (!console::created()) {
			console::create(800, 600);
			console::show();
		} 

		if (!console::visible()) console::show();
	}	
	
	void SystemConsoleLogger::internalLog(const String& from, const String& message, const LogLevel level, const console::ConsoleColor color) const {
		console::textColor(color);

		// Format out.
		String out;

		formatOut(out, from, message, level);

		// Write and reset color.
		console::writeLine(out);

		console::resetColor();
	}

	void SystemConsoleLogger::logError(const String& from, const String& message) {
		internalLog(from, message, LogLevel::Error, console::ConsoleColor::Red);
	}
	void SystemConsoleLogger::logWarning(const String& from, const String& message) {
		internalLog(from, message, LogLevel::Warning, console::ConsoleColor::Yellow);
	}
	void SystemConsoleLogger::logInfo(const String& from, const String& message) {
		internalLog(from, message, LogLevel::Info, console::ConsoleColor::DarkGreen);
	}
}