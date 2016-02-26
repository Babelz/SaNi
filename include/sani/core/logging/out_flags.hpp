#pragma once

#include "sani/types.hpp"

namespace sani {

	namespace log {

		/// Where the log message should me written.
		enum class OutFlags : int8 {
			/// Message will be written to the system
			/// console.
			SystemConsole	= 1,

			/// Message will be written to log file.
			File			= 2,

			/// All loggers will receive this message.
			All				= SystemConsole & File
		};

		OutFlags operator &(const OutFlags lhs, const OutFlags rhs);
	}
}