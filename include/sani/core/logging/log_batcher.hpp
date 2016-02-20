#pragma once

#include "sani/forward_declare.hpp"
#include "sani/core/logging/log_level.hpp"
#include "sani/forward_declare.hpp"
#include "sani/types.hpp"
#include <list>

namespace sani {

	struct LogBatchEntry final {
		String line;
		LogLevel level;
		uint32 scope;

		LogBatchEntry(const String& line, const LogLevel level, const uint32 scope);
		LogBatchEntry(const String& line, const LogLevel level);
		LogBatchEntry();

		~LogBatchEntry() = default;
	};

	/// @class LogBatcher log_batcher.hpp "sani/core/logging/log_batcher.hpp"
	/// @author voidbab
	///
	/// Utility class that can be used to log and format many
	/// messages until writing or presenting them to the user.
	class LogBatcher final {
	private:
		String ident;
		String from;
		String name;
		uint32 scope;

		std::list<LogBatchEntry> entries;
	public:
		LogBatcher();

		/// Returns the ident string to the user.
		const String& getIdent() const;
		/// Sets the ident string.
		void setIdent(const String& ident);

		/// Begins logging, resets state data.
		/// @param[in] from who called? what are we logging?
		/// @param[in] name name of the batch
		void beginLog(const String& from, const String& name);

		void logError(const String& message);
		void logWarning(const String& message);
		void logInfo(const String& message);

		/// Increase the scope (ident) by one.
		void scopeStart();
		/// Decrease the scope by one.
		void scopeEnd();

		/// Writes end string to the logger.
		void endLog();

		/// "Collapse" the batch to given logger.
		template<class T>
		void log(T& logger) const;

		~LogBatcher() = default;
	};
}

#include "sani/core/logging/impl/log_batcher.hpp"