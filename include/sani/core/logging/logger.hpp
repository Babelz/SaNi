#pragma once

#include "sani/core/logging/log_level.hpp"
#include "sani/types.hpp"

namespace sani {

	using OutputStream = std::ostream;

	/// @class Logger logger.hpp "sani/core/logging/logger.hpp"
	/// @author voidbab
	/// 
	/// Serves as a base class for all loggers.
	template<class T>
	class Logger {
	private:
		// Name of the logger.
		const String name;
	protected:
		Logger(const String& name);
	public:
		virtual ~Logger() = default;

		const String& getName() const;

		/// Calls appropriate log function determined by the log level. From can be the subroutines name or the 
		/// location from where the logging happens.
		void log(const String& from, const LogLevel logLevel, const String& message);

		/// Logs an error. From can be the subroutines name or the 
		/// location from where the logging happens.
		void logError(const String& from, const String& message);
		/// Logs an warning. From can be the subroutines name or the 
		/// location from where the logging happens.
		void logWarning(const String& from, const String& message);
		/// Logs some info. From can be the subroutines name or the 
		/// location from where the logging happens.
		void logInfo(const String& from, const String& message);
	};
}

#include "sani/core/logging/impl/logger.hpp"