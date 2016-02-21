#pragma once

namespace sani {

	/// Contains the "levels" that
	/// we can log.
	enum class LogLevel {
		/// Handles the incoming log message as an error.
		Error,

		/// Handles the incoming log message as an warning.
		Warning,

		/// Handles the incoming log message as general
		/// information.
		Info
	};
}