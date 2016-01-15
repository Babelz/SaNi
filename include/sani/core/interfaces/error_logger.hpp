#pragma once

#include "sani/types.hpp"
#include <stack>

namespace sani {

	namespace interfaces {

		using ErrorBuffer = std::stack<String>;

		/// @class ErrorLogger error_logger.hpp "sani/core/interfaces/error_logger.hpp"
		/// @author voidbab
		/// 
		/// Interface that consumers use to log internal errors.
		class ErrorLogger {
		private:
			ErrorBuffer errors;
		protected:
			/// Push new error to the logger.
			void pushError(const String& error);
			
			/// Copies errors from the other logger. 
			/// This clears the other loggers error buffer.
			void copyErrors(ErrorLogger& other);
		public:
			ErrorLogger() = default;

			/// Returns true if the logger has logged errors.
			bool hasErrors() const;
			/// Returns the next error to the caller.
			/// Errors are returned in reversed order.
			String getNextError();

			virtual ~ErrorLogger() = default;
		};
	}
}