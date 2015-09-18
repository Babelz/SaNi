#pragma once

#include "sani/core/cvar/cvar_statement.hpp"
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
	/// Represents non-generic cvar.
	class CVar {
	private:
		const CVarRequireStatement statement;
		const cvarlang::ValueType type;
		const String name;
		const bool synced;

		void* data;
	public:
		CVar(const CVarRequireStatement& statement, const cvarlang::ValueType type, 
			 const String& name, const bool synced, void* data);

		/// Returns the value type of this cvar.
		cvarlang::ValueType getType() const;
		/// Returns the name of this cvar.
		const String& getName() const;
		
		/// Returns true if caller can change the value of this cvar.
		bool canWrite() const;
		/// Returns true if this cvar should be synced.
		bool isSynced() const;
		
		/// Returns the value of this cvar.
		void* read() const;
		/// Writes the given value to this cvar.
		void write(void* data);
		
		~CVar();
	};
}