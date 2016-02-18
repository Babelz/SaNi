#pragma once

#include "sani/types.hpp"

namespace sani {

	using OutputStream = std::ostream;

	enum class LogLevel {
		Error,
		Warning,
		Info
	};

	template<class T>
	class Logger {
	private:
		const String name;
	protected:
		Logger(const String& name);
	public:
		virtual ~Logger() = default;

		const String& getName() const;

		void log(const String& from, const LogLevel logLevel, const String& message);
		
		void logError(const String& from, const String& message);
		void logWarning(const String& from, const String& message);
		void logInfo(const String& from, const String& message);
	};
}