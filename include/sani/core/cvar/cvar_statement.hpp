#pragma once

#include "sani/core/cvar/cvar_condition.hpp"
#include <vector>

namespace sani {

	/// @class CVarRequireStatement cvar_statement.hpp "sani/core/cvar/cvar_statement.hpp"
	/// @author voidbab
	///
	/// Represents a set of conditions.
	class CVarRequireStatement {
	private:
		const std::vector<CVarCondition> conditions;
		const String message;
	public:
		CVarRequireStatement(const std::vector<CVarCondition>& conditions, const String& message);

		const String& getMessage() const;

		~CVarRequireStatement();

		/// Returns whether the condition was met.
		bool operator()() const;

		bool operator == (const CVarRequireStatement& other) const;
		bool operator != (const CVarRequireStatement& other) const;
	};
}