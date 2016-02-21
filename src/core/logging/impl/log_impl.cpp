#include "sani/core/logging/system_console_logger.hpp"
#include "sani/core/logging/impl/log_impl.hpp"
#include "sani/core/logging/file_logger.hpp"
#include "sani/core/logging/out_flags.hpp"

namespace sani {

	namespace log {

		LogImpl::LogImpl() {
			const String logFilePath = "log.txt";

			loggers[NullLogger] = nullptr;
			loggers[static_cast<uint32>(OutFlags::SystemConsole)] = new SystemConsoleLogger();
			loggers[static_cast<uint32>(OutFlags::File)] = new FileLogger(logFilePath);
		}

		LogImpl::~LogImpl() {
			delete loggers[static_cast<uint32>(OutFlags::SystemConsole)];
			delete loggers[static_cast<uint32>(OutFlags::File)];
		}
	}
}