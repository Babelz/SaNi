#include "sani/core/cvar/cvar_condition.hpp"

namespace sani {

	/*
		CVarCondition class impl.
	*/

	CVarCondition::CVarCondition(const cvarlang::Operator oper, const Condition condition) : oper(oper),
																							 condition(condition) {
	}

	cvarlang::Operator CVarCondition::getOperator() const {
		return oper;
	}

	CVarCondition::~CVarCondition() {
	}

	bool CVarCondition::operator()() const {
		return condition();
	}

	/*
		CVarRequirementStatement class impl.
	*/

	CVarRequireStatement::CVarRequireStatement(const std::vector<CVarCondition>& statement) : statement(statement),
																							  capacity(0) {
		// Compute capacity.
		size_t i = 0;

		while (i < statement.size()) {
			if (statement[i].getOperator() == cvarlang::Operator::None) { i++; capacity++; }
			else														{ i += 2; capacity += 2; }
		}
	}

	CVarRequireStatement::~CVarRequireStatement() {
	}

	/// Returns whether the condition was met.
	bool CVarRequireStatement::operator()() {
		// 1) oper == none, check.
		// 2) oper != none, take next for checking aswell.

		/*
			bool, bool
			require (i < 10 && a == 10 || b != 10)  cvarlang::Operator::And, cvarlang::Operator::Or

			bool
			require (i < 10 && a == 10)				cvarlang::Operator::And, cvarlang::Operator::None

			bool, bool
			require (i < 10 && a == 10 || c && d || a || b || c || d)

			bool
			require (a == 10)						cvarlang::Operator::None
		*/

		// Interpret.
		bool lastResult = false;
		bool result = false;
		size_t i = 0;

		while (i < statement.size()) {
			CVarCondition* current = &statement[i];
			CVarCondition* second = nullptr;

			if (statement[i].getOperator() == sani::cvarlang::None) {
				result = (*current)();
				
				i++;
			} else if (statement[i].getOperator() == sani::cvarlang::And) {
				// Post inc to get next.
				i++;

				lastResult = result;

				second = &statement[i];
				result = (*current)() && (*second)();

				// Pre inc to get first at next iteration.
				i++;
			} else if (statement[i].getOperator() == sani::cvarlang::Or) {
				bool orResult = false;
				bool beforeOr = result;

				// || a || b || c 
				while (i < statement.size() || current->getOperator() == cvarlang::Operator::Or) {
					// Get cur + 1 element.
					if (i > 0) lastResult = result;
					else	   { i++; lastResult = statement[i](); }

					// True found, return.
					if (orResult) break;

					// Compute results.
					orResult = (*current)() || lastResult;
					result = orResult;

					// Get next. cur + 1.
					if (i == 0)				  i++;
					if (i < statement.size()) current = &statement[i];
				}
				
				// Left side was true. Swap.
				if (!orResult && beforeOr) result = beforeOr;
			} else {
				throw std::logic_error("Invalid or unsupported cvarlang::Operator");
			}
		}

		return result;
	}
}