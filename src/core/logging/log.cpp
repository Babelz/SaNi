#include "sani/debug.hpp"
#include "sani/core/logging/log.hpp"
#include "sani/core/logging/log_batcher.hpp"
#include "sani/core/logging/file_logger.hpp"
#include "sani/core/logging/system_console_logger.hpp"

namespace sani {

	namespace log {

		struct Impl {
			// Add one to keep first ass nullptr.
			const uint32 LoggersCount = OutStreamsCount + 1;
			void* loggers[3];

			Impl() {
				const String logFilePath	= "log.txt";

				loggers[OutFlagsNull]		= nullptr;
				loggers[OutFlagsConsole]	= new SystemConsoleLogger();
				loggers[OutFlagsFile]		= new FileLogger(logFilePath);
			}

			~Impl() = default;
		};

		void initialize() {
			impl = new Impl();
		}
		void deinitialize() {
			delete impl;
		}

		template<class T>
		static void tryToLog(const uint16 id, const String& from, const String& message, const LogLevel level) {
			if (id == OutFlagsNull) return;
			
			static_cast<T*>(impl->loggers[id])->log(from, level, message);
		}
		template<class T>
		static void internalBatch(const uint16 id, LogBatcher& batcher) {
			if (id == OutFlagsNull) return;

			void* logger = impl->loggers[id];

			batcher.log<T>(*static_cast<T*>(logger));
		}

		static void internalLog(const uint16 outFlags, const String& from, const String& message, const LogLevel level) {
			uint16 isConsoleOut = (outFlags >> 0) & 1 * 1;
			uint16 isFileOut	= (outFlags >> 1) & 1 * 2;

			tryToLog<SystemConsoleLogger>(isConsoleOut, from, message, level);
			tryToLog<FileLogger>(isFileOut, from, message, level);
		}

		void error(const uint16 outFlags, const String& from, const String& message) {
			internalLog(outFlags, from, message, LogLevel::Error);
		}
		void warning(const uint16 outFlags, const String& from, const String& message) {
			internalLog(outFlags, from, message, LogLevel::Warning);
		}
		void info(const uint16 outFlags, const String& from, const String& message) {
			internalLog(outFlags, from, message, LogLevel::Info);
		}

		void batch(const uint16 outFlags, LogBatcher& batcher) {
			uint16 isConsoleOut = (outFlags >> 0) & 1 * 1;
			uint16 isFileOut	= (outFlags >> 1) & 1 * 2;

			internalBatch<SystemConsoleLogger>(isConsoleOut, batcher);
			internalBatch<FileLogger>(isFileOut, batcher);
		}
	}
}