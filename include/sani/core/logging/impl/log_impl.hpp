#pragma once

#include "sani/core/logging/out_flags.hpp"
#include <array>

namespace sani {

	namespace log {

		template<uint32 Size>
		using Loggers = std::array<void*, Size>;


		const uint32 LoggersCount	= 2;
		const uint32 NullLogger		= 0;

		/// @class LogImpl log_impl.hpp "sani/core/logging/impl/log_impl.hpp"
		/// @author voidbab
		/// 
		/// Contains implementation for the logger
		/// that is being used from the log namespace.
		struct LogImpl final {
			Loggers<LoggersCount + 1> loggers;

			LogImpl();

			~LogImpl();
		};
	}
}