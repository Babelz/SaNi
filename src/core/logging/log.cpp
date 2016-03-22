#include "sani/debug.hpp"
#include "sani/core/logging/log.hpp"
#include "sani/core/logging/log_batcher.hpp"
#include "sani/core/logging/file_logger.hpp"
#include "sani/core/logging/system_console_logger.hpp"

namespace sani {

	namespace log {

		static LogImpl impl;

		template<class T>
		static void logTo(const uint16 id, const String& from, const String& message, const LogLevel level) {
			if (id == NullLogger) return;
			
			static_cast<T*>(impl.loggers[id])->log(from, level, message);
		}
		template<class T>
		static void internalBatch(const uint16 id, LogBatcher& batcher) {
			if (id == NullLogger) return;

			batcher.log<T>(*static_cast<T*>(impl.loggers[id]));
		}

		static void internalLog(const OutFlags outFlags, const String& from, const String& message, const LogLevel level) {
			const uint16 isConsoleOut = (static_cast<uint32>(outFlags) >> 0) & 1;
			const uint16 isFileOut = (static_cast<uint32>(outFlags) >> 1) & 1;

			// Mul by index to translate to id.
			logTo<SystemConsoleLogger>(isConsoleOut * 1, from, message, level);
			logTo<FileLogger>(isFileOut * 2, from, message, level);
		}

		namespace __privns__ {
			
			void error(const OutFlags outFlags, const String& from, const String& message) {
				internalLog(outFlags, from, message, LogLevel::Error);
			}
			void warning(const OutFlags outFlags, const String& from, const String& message) {
				internalLog(outFlags, from, message, LogLevel::Warning);
			}
			void info(const OutFlags outFlags, const String& from, const String& message) {
				internalLog(outFlags, from, message, LogLevel::Info);
			}
		}

		void batch(const OutFlags outFlags, LogBatcher& batcher) {
			const uint32 outFlagsi = static_cast<uint32>(outFlags);

			uint16 isConsoleOut = (outFlagsi >> 0) & 1;
			uint16 isFileOut	= (outFlagsi >> 1) & 1;

			// Mul by index to translate to id.
			internalBatch<SystemConsoleLogger>(isConsoleOut * 1, batcher);
			internalBatch<FileLogger>(isFileOut * 2, batcher);
		}
	}
}