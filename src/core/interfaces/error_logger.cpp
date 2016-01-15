#include "sani/core/interfaces/error_logger.hpp"

namespace sani {
	
	namespace interfaces {

		bool ErrorLogger::hasErrors() const {
			return !errors.empty();
		}
		String ErrorLogger::getNextError() {
			if (hasErrors()) {
				const String next = errors.top();
				errors.pop();

				return next;
			}

			// No errors left, return empty string.
			return String();
		}
	}
}