#pragma once

#include "sani/core/logging/log_level.hpp"
#include "sani/types.hpp"

namespace sani {

	using OutputStream = std::ostream;

	/// @class Logger logger.cpp "sani/core/logging/logger.hpp"
	/// @author voidbab
	/// 
	/// Serves as a base class for all loggers.
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

#include "sani/core/logging/impl/logger.hpp"