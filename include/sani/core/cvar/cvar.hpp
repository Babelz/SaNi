#pragma once

#include "sani/core/cvar/cvar_statement.hpp"
#include "sani/precompiled.hpp"
#include <list>

namespace sani {

	/// @class CVar cvar.hpp "sani/core/cvar/cvar.hpp"
	/// @author voidbab
	///
	/// Represents non-generic cvar.
	class CVar {
	private:
		// Wrap some value field types to union
		// so we can save few bytes at best.
		union {
			int32 int32Val;
			float32 float32Val;
			float64 float64Val;
		};

		// TODO: could this be moved to an union by any chance?
		String stringVal;

		const std::list<CVarRequireStatement> statements;
		const cvarlang::ValueType type;
		const String name;

		const bool synced;
		bool changed;

		// To share common init logic between ctors. Can't use 
		// delegation as other ctor does not need the statement list.
		void initialize(const String& value);
	public:
		CVar(const cvarlang::ValueType type, const String& name, const bool synced, const String& value);

		CVar(const std::list<CVarRequireStatement>& statements, const cvarlang::ValueType type,
			const String& name, const bool synced, const String& value);

		/// Creates a new cvar with default value of given value type.
		CVar(const cvarlang::ValueType type, const String& name);

		/// Returns the value type of this cvar.
		cvarlang::ValueType getType() const;
		/// Returns the name of this cvar.
		const String& getName() const;

		/// Returns true if caller can change the value of this cvar.
		bool canWrite() const;

		/// Returns true if the value has changed during the 
		/// runtime.
		bool hasChanged() const;
		/// Returns true if this cvar should be synced.
		bool isSynced() const;

		void read(String& value) const;
		void read(int32& value) const;
		void read(float32& value) const;
		void read(float64& value) const;

		void write(const String& value);
		void write(int32 value);
		void write(float32 value);
		void write(float64 value);

		void getRequireStatementMessages(std::vector<String>& messages);

		~CVar();

		const bool operator == (const CVar& other) const;
		const bool operator != (const CVar& other) const;
		const bool operator < (const CVar& other) const;
		const bool operator <= (const CVar& other) const;
		const bool operator > (const CVar& other) const;
		const bool operator >= (const CVar& other) const;
	};
}
