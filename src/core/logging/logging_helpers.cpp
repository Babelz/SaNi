#include "sani/core/logging/logging_helpers.hpp"

namespace sani {

	void formatError(const String& from, String& error) {
		error = "[" + from + "(ERR)]: " + error;
	}

	void formatWarning(const String& from, String& warning) {
		warning = "[" + from + "(ERR)]: " + warning;
	}

	void formatInfo(const String& from, String& info) {
		info = "[" + from + "(ERR)]: " + info;
	}
}