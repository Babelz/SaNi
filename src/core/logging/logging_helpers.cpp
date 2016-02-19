#include "sani/core/logging/logging_helpers.hpp"
#include "sani/core/logging/log_level.hpp"

namespace sani {

	void formatOut(String& out, const String& from, const String& message, const LogLevel level) {
		switch (level) {
		case LogLevel::Error:
			formatError(out, from, message);
			break;
		case LogLevel::Warning:
			formatWarning(out, from, message);
			break;
		case LogLevel::Info:
			formatInfo(out, from, message);
			break;
		default:
			throw std::runtime_error("invalid or unsupported level");
		}
	}

	void formatError(String& out, const String& from, const String& error) {
		out = "[" + from + "(ERR)]: " + error;
	}

	void formatWarning(String& out, const String& from, const String& warning) {
		out = "[" + from + "(WARN)]: " + warning;
	}

	void formatInfo(String& out, const String& from, const String& info) {
		out = "[" + from + "(INFO)]: " + info;
	}
}