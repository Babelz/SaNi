#pragma once

#include "sani/forward_declare.hpp"
#include "sani/core/logging/logger.hpp"

SANI_FORWARD_DECLARE_ENUM_CLASS_2(sani, console, ConsoleColor);

namespace sani {

	class SystemConsoleLogger final : public Logger<SystemConsoleLogger> {
	private:
		void internalLog(const String& from, const String& message, const LogLevel level, const console::ConsoleColor color) const;
	public:
		SystemConsoleLogger();

		void logError(const String& from, const String& message);
		void logWarning(const String& from, const String& message);
		void logInfo(const String& from, const String& message);

		// Should the logger close the system console once it 
		// gets destroyed?
		virtual ~SystemConsoleLogger() = default;
	};
}