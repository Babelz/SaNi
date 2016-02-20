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

	class LogBatcher final {
	private:
		String ident;
		String from;
		String name;
		uint32 scope;

		std::list<LogBatchEntry> entries;
	public:
		LogBatcher();

		const String& getIdent() const;
		void setIdent(const String& ident);

		void beginLog(const String& from, const String& name);

		void logError(const String& message);
		void logWarning(const String& message);
		void logInfo(const String& message);

		void scopeStart();
		void scopeEnd();

		template<class T>
		void log(T& logger);

		~LogBatcher() = default;
	};
}

#include "sani/core/logging/impl/log_batcher.hpp"