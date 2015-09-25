#include "sani/core/cvar/cvar_parser.hpp"
#include "sani/core/utils/string_utils.hpp"
#include <list>

namespace sani {

	CVarParser::CVarParser() {
	}

	void CVarParser::pushError(const String& error) {
		errorBuffer.push(error);
	}

	void CVarParser::findLogicalOperator(const String& str, size_t& pos) const {
		if (cvarlang::lang::containsLogicalAnd(str))	pos = str.find(cvarlang::lang::And);
		if (cvarlang::lang::containsLogicalOr(str))		pos = str.find(cvarlang::lang::Or);
	}

	void CVarParser::findConditionalOperator(const String& str, size_t& pos, size_t& len) {
		if (cvarlang::lang::containsEqualOperator(str)) {
			pos = str.find(cvarlang::lang::Equal);
			len = cvarlang::lang::Equal.size();
		} else if (cvarlang::lang::containsNotEqualOperator(str)) {
			pos = str.find(cvarlang::lang::NotEqual);
			len = cvarlang::lang::NotEqual.size();
		} else if (cvarlang::lang::containsSmallerOperator(str)) {
			pos = str.find(cvarlang::lang::Smaller);
			len = cvarlang::lang::Smaller.size();
		} else if (cvarlang::lang::containsSmallerOrEqualOperator(str)) {
			pos = str.find(cvarlang::lang::SmallerOrEqual);
			len = cvarlang::lang::SmallerOrEqual.size();
		} else if (cvarlang::lang::containsGreaterOperator(str)) {
			pos = str.find(cvarlang::lang::Greater);
			len = cvarlang::lang::Greater.size();
		} else if (cvarlang::lang::containsGreaterOrEqualOperator(str)) {
			pos = str.find(cvarlang::lang::GreaterOrEqual);
			len = cvarlang::lang::GreaterOrEqual.size();
		}

		// Check for errors.
		if (len == 0) pushError(SANI_WARNING_MESSAGE("invalid or unsupported operator, skipping compilation, line is \"" + str + "\""));
	}

	void CVarParser::parseConditionalExpression(String& exprStr, cvarlang::IntermediateCondition& intermediateCondition) {
		// Trim the input just to be sure it does not contain any whitespace.
		utils::trim(exprStr);

		if (cvarlang::lang::containsConditionalOperators(exprStr)) {
			// Split by operators.

			size_t conPos = 0;
			size_t logPos = 0;
			size_t len = 0;

			findConditionalOperator(exprStr, conPos, len);

			if (cvarlang::lang::containsLogicalOperators(exprStr)) findLogicalOperator(exprStr, logPos);

			String lhs = exprStr.substr(0, conPos);
			String oper = exprStr.substr(conPos, len);
			String rhs = exprStr.substr(conPos + len, logPos - conPos - len);

			utils::trim(lhs);
			utils::trim(oper);
			utils::trim(rhs);

			// Fill.
			intermediateCondition.lhs = lhs;
			intermediateCondition.rhs = rhs;
			intermediateCondition.conditionalOperator = cvarlang::stringToConditionalOperator(oper);
			intermediateCondition.lhsIsConst = cvarlang::lang::isConstValue(lhs);
			intermediateCondition.rhsIsConst = cvarlang::lang::isConstValue(rhs);

			exprStr = exprStr.substr(logPos);
		} else {
			// Should be an constant bool expression as there are no operators.
			String lhs;
			
			if (cvarlang::lang::containsLogicalOperators(exprStr)) {
				size_t pos = 0;

				findLogicalOperator(exprStr, pos);

				lhs = exprStr.substr(0, pos);

				exprStr = exprStr.substr(pos);
			} else {
				lhs = exprStr;
			}

			utils::trim(lhs);

			// Fill.
			intermediateCondition.lhs = lhs;
			intermediateCondition.lhsIsConst = cvarlang::lang::isConstValue(lhs);

			exprStr = exprStr.substr(lhs.size());
		}

		// Find the possible logical operator.
		if (cvarlang::lang::containsLogicalOperators(exprStr)) {
			size_t pos = 0;

			findLogicalOperator(exprStr, pos);

			String oper = exprStr.substr(pos, 2);

			intermediateCondition.logicalOperator = cvarlang::stringToLogicalOperator(oper);

			exprStr = exprStr.substr(2);
		}

		// TODO: test.
	}

	bool CVarParser::hasErrors() const {
		return errorBuffer.size() != 0;
	}
	String CVarParser::getNextError() {
		String error(errorBuffer.top());
		errorBuffer.pop();

		return error;
	}

	void CVarParser::parseCvar(String str, cvarlang::IntermediateCVar& intermediateCVar) {
		// Split into tokens. Should be splitted by whitespace.
		std::vector<String> tokens;

		// Remove any comments, we don't need them here.
		if (cvarlang::lang::containsComment(str)) {
			const size_t len = str.find(cvarlang::lang::Comment);

			str = str.substr(0, len);
		}

		utils::split(str, String(" "), tokens, true);
		utils::trim(str);

		// Too many or too few tokens.
		if (tokens.size() != 2) {
			if		(tokens.size() < 2) pushError(SANI_WARNING_MESSAGE("too few tokens, skipping compilation, line is \"" + str + "\""));
			else						pushError(SANI_WARNING_MESSAGE("too many tokens, skipping compilation, line is \"" + str + "\""));
			
			return;
		}

		cvarlang::ValueType type = cvarlang::ValueType::NoValue;
		String name = tokens[0];
		String value = tokens[1];
		
		// Resolve the type of the variable.
		if		(cvarlang::lang::isStringDeclaration(str))		type = cvarlang::ValueType::StringVal;
		else if (cvarlang::lang::isIntDeclaration(str))			type = cvarlang::ValueType::IntVal;
		else if (cvarlang::lang::isFloatDeclaration(str))		type = cvarlang::ValueType::FloatVal;
		else if (cvarlang::lang::isDoubleDeclaration(str))		type = cvarlang::ValueType::DoubleVal;

		// Check for invalid value string.
		if (type == cvarlang::ValueType::NoValue) {
			pushError(SANI_WARNING_MESSAGE("unsupported or invalid value declaration, line is \"" + str + "\""));

			return;
		}

		// Trim values.
		utils::trim(name);
		utils::trim(value);

		// Fill the intermediate representation.
		intermediateCVar.name = name;
		intermediateCVar.type = type;
		intermediateCVar.value = value;
	}
	void CVarParser::parseRequireStatement(String reqStr, const String& msgStr, cvarlang::IntermediateRequireStatement& intermediateRequirementStatement) {
		if (cvarlang::lang::containsComment(reqStr)) {
			const size_t len = reqStr.find(cvarlang::lang::Comment);

			reqStr = reqStr.substr(0, len);
		}

		while (reqStr.size() > 0) {
			intermediateRequirementStatement.conditions.push_back(cvarlang::IntermediateCondition());

			parseConditionalExpression(reqStr, intermediateRequirementStatement.conditions.back());
		}
 	}

	CVarParser::~CVarParser() {
	}
}