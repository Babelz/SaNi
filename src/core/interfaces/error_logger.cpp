#include "sani/core/interfaces/error_logger.hpp"

namespace sani {
	
	namespace interfaces {

		/// Push new error to the logger.
		void ErrorLogger::pushError(const String& error) {
			errors.push(error);
		}

		void ErrorLogger::copyErrors(ErrorLogger& other) {
			while (other.hasErrors()) pushError(other.getNextError());
		}

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