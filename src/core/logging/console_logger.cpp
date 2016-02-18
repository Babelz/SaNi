#include "sani/core/logging/system_console_logger.hpp"
#include "sani/platform/console.hpp"

namespace sani {

	SystemConsoleLogger::SystemConsoleLogger() : Logger<SystemConsoleLogger>("system console logger") {
		if (!console::created()) {
			console::create(800, 600);
			console::show();
		}
	}

	void SystemConsoleLogger::logError(const String& from, const String& message) {
	}
	void SystemConsoleLogger::logWarning(const String& from, const String& message) {
	}
	void SystemConsoleLogger::logInfo(const String& from, const String& message) {
	}
}