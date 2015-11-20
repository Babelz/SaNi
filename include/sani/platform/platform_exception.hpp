#pragma once

#include <exception>
#include "sani/types.hpp"

namespace sani {
	class UnsupportedOperation : public std::exception {
	private:
		String msg;
	public:
		UnsupportedOperation(const String& msg)
			: msg(msg) { }
		
		virtual const char* what() const throw() {
			return !msg.empty() ? msg.c_str() :  "This operation is not supported";
		}
	};
}