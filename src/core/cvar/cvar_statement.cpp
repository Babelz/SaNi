#include "sani/core/cvar/cvar_statement.hpp"

namespace sani {

	CVarRequireStatement::CVarRequireStatement(const std::vector<CVarCondition>& statement) : statement(statement) {
	}

	CVarRequireStatement::~CVarRequireStatement() {
	}

	bool CVarRequireStatement::operator()() const {
		/*
			TODO: idk, looks kinda funkeyyYY, maybe refactor?
				  could fix with a transition table.
		*/

		// Interpret.
		bool lastResult = false;
		bool result = false;
		size_t i = 0;

		while (i < statement.size()) {
			const CVarCondition* current = &statement[i];
			const CVarCondition* second = nullptr;

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