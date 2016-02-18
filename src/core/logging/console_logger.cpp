#include "sani/core/logging/system_console_logger.hpp"
#include "sani/platform/console.hpp"

namespace sani {

	SystemConsoleLogger::SystemConsoleLogger() : Logger<SystemConsoleLogger>("system console logger") {
		if (!console::created()) {
			console::create(800, 600);
			console::show();
		} 

		if (!console::visible()) console::show();
	}

	void SystemConsoleLogger::logError(const String& from, const String& message) {
		console::textColor(console::ConsoleColor::Red);

		console::writeLine("[" + from + "(ERR)]: " + message);

		console::resetColor();
	}
	void SystemConsoleLogger::logWarning(const String& from, const String& message) {
		console::textColor(console::ConsoleColor::Yellow);

		console::writeLine("[" + from + "(WRN)]: " + message);

		console::resetColor();
	}
	void SystemConsoleLogger::logInfo(const String& from, const String& message) {
		console::textColor(console::ConsoleColor::DarkGreen);

		console::writeLine("[" + from + "(NFO)]: " + message);

		console::resetColor();
	}
}