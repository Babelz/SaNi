#include "sani/core/logging/log.hpp"
#include "sani/core/logging/log_batcher.hpp"
#include "sani/core/logging/file_logger.hpp"
#include "sani/core/logging/system_console_logger.hpp"

namespace sani {

	namespace log {

		struct Impl {
			// Add one to keep first index as null.
			void* loggers;

			Impl() {
				const uint32 loggersSize = sizeof(SystemConsoleLogger) + sizeof(FileLogger);
				
			}

			~Impl() = default;
		};

		void initialize() {
			impl = new Impl();
		}
		void deinitialize() {
			delete impl;
		}

		void error(const uint16 outFlags, const String& from, const String& message) {
			uint16 consoleOut = (outFlags >> 0) & 1 * 1;
			uint16 fileOut = (outFlags >> 1) & 1 * 2;
		}
		void warning(const uint16 outFlags, const String& from, const String& message) {
		}
		void info(const uint16 outFlags, const String& from, const String& message) {
		}

		void batch(const uint16 outFlags, LogBatcher& batcher) {
		}
	}
}