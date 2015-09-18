#pragma once

#include "sani/precompiled.hpp"

namespace sani {

	namespace cvarlang {
		
		enum ValueType {
			String,
			// 32-bit integer.
			Int,
			// 32-bit floating point number.
			Float,
			// 64-bit floating point number.
			Double
		};
	}

	/// @class CVar cvar.hpp "sani/core/cvar/cvar.hpp"
	/// @author voidbab
	///
	/// Represents a non-generic cvar.
	class CVar {
	private:
		const cvarlang::ValueType type;
		const String name;
		const bool synced;

		void* data;
	public:
	};
}