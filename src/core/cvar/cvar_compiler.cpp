#include "sani/core/cvar/cvar_tokenizer.hpp"
#include "sani/core/cvar/cvar_compiler.hpp"
#include "sani/core/cvar/cvar_loader.hpp"
#include "sani/core/cvar/cvar_parser.hpp"
#include "sani/core/cvar/cvar_lang.hpp"

namespace sani {

	CVarCompiler::CVarCompiler() : synced(false) {
	}

	void CVarCompiler::copyErrors(CVarParser* parser) {
		while (parser->hasErrors()) errorBuffer.push(parser->getNextError());
	}
	void CVarCompiler::copyErrors(CVarTokenizer* tokenizer) {
		while (tokenizer->hasErrors()) errorBuffer.push(tokenizer->getNextError());
	}

	bool CVarCompiler::hasErrors() const {
		return errorBuffer.size() != 0;
	}
	String CVarCompiler::getNextError() {
		String error(errorBuffer.top());
		errorBuffer.pop();

		return error;
	}

	void CVarCompiler::generateCVars(std::list<CVar>& cvars, std::list<CVarRecord>& records, std::list<CVarToken>& tokens) {
		// 1) Process token
		// 2) Parse it
		// 3) Check for errors
		// 4) Emit cvar or statement
		// 5) generate record

		CVarParser parser;

		std::list<cvarlang::IntermediateCVar> intermediateCVar;
		std::list<cvarlang::IntermediateRequireStatement> intermediateRequireStatement;
		std::list<CVarRequireStatement> statements;
		// Current scope level. Gets decreased when require keyword is found,
		// and gets increased when require statement is found.
		size_t scope = 0;

		// Go trough each token.
		auto i = tokens.begin();
		while (i != tokens.end()) {
			// Only process declaration and require tokens.
			// Anything but these are just pure garbage.
			// We still keep these tokens for the parsing process.
			// Who knows if we need them some day (when the lexical analyzer evolves OSLT)
			if (i->getType() == cvarlang::TokenType::Declaration) {
				cvarlang::IntermediateCVar intermediateCVar;

				parser.parseCvar(i->getLine(), intermediateCVar);

				if (parser.hasErrors()) copyErrors(&parser);

				// Emit cvar.
				generateCVar(cvars, statements, &intermediateCVar);

				if (synced) {
					// Emit record.
					generateRecord(records, *i, cvars.back());
				}
			}
			else if (i->getType() == cvarlang::TokenType::Require) {
				// So, the require token class has 2 variants, the one 
				// that starts a require statement (require([condition]) and 
				// the one that ends a block, that is just the plain require keyword in use.
				// We need to track that the user closes the scopes before the tokens end,
				// or we are fucked.

				cvarlang::IntermediateRequireStatement intermediateRequireStatement;
				String message;

				// Check if the next one is a message statement.
				auto next = std::next(i, 1);

				if (next != tokens.end()) {
					if ((next)->getType() == cvarlang::TokenType::Message) {
						message = (next)->getLine();

						i++;
					}
				}

				parser.parseRequireStatement(i->getLine(), message, intermediateRequireStatement);

				if (intermediateRequireStatement.blockEnding) {
					if (scope > 0) {
						statements.remove(statements.back());
						scope--;
					}

					continue;
				}

				generateRequireStatement(statements, cvars, &intermediateRequireStatement);
			}

			i++;

			if (hasErrors()) return;
		}
	}

	void CVarCompiler::generateCVar(std::list<CVar>& cvars, std::list<CVarRequireStatement>& statements, const cvarlang::IntermediateCVar* intermediateCVar) {
		cvars.push_back(CVar(statements, intermediateCVar->type, intermediateCVar->name, synced, intermediateCVar->value));
	}
	void CVarCompiler::generateRecord(std::list<CVarRecord>& records, const CVarToken& token, const CVar& cvar) const {
		records.push_back(CVarRecord(token, cvar));
	}

	void CVarCompiler::generateRequireStatement(std::list<CVarRequireStatement>& statements, std::list<CVar>& cvars, const cvarlang::IntermediateRequireStatement* intermediateRequireStatement) {
		std::vector<CVarCondition> conditions;

		/*
			TODO: missing the boolean not (!) operator for bool expressions.
			They could come handy.
		*/

		for (const cvarlang::IntermediateCondition& intermediateCondition : intermediateRequireStatement->conditions) {
			if (intermediateCondition.lhs.size() > 0 || intermediateCondition.rhs.size() > 0) {
				Condition condition;

				if		(intermediateCondition.lhsIsConst && intermediateCondition.rhsIsConst)			generateConstConstExpression(&intermediateCondition, condition);				 // Const oper const
				else if (intermediateCondition.rhsIsConst && !intermediateCondition.lhsIsConst)			generateConstCVarExpression(&intermediateCondition, condition, cvars);			 // Const oper cvar
				else if (!intermediateCondition.rhsIsConst && intermediateCondition.lhsIsConst)			generateCVarConstExpression(&intermediateCondition, condition, cvars);		     // Cvar oper const
				else if (intermediateCondition.lhs.size() > 0 && intermediateCondition.rhs.size() == 0)	generateConstCVarBoolExpression(&intermediateCondition, condition, cvars);		 // CVar
				else if (intermediateCondition.lhs.size() > 0 && intermediateCondition.lhsIsConst)		generateConstBoolConstExpression(&intermediateCondition, condition, cvars);		 // Const
			}
		}

		statements.push_back(CVarRequireStatement(conditions, intermediateRequireStatement->message));
	}

	void CVarCompiler::generateConstConstExpression(const cvarlang::IntermediateCondition* intermediateCondition, Condition& condition) {
		// Const oper const.

		/*
			TODO: could store temps some where incase they are needed?
		*/

		CVar lhs(intermediateCondition->lhsType, String("___TEMP_CVAR___"), false, intermediateCondition->lhs);
		CVar rhs(intermediateCondition->rhsType, String("___TEMP_CVAR___"), false, intermediateCondition->rhs);

		condition = [&lhs, &rhs]() {
			return lhs == rhs;
		};
	}
	void CVarCompiler::generateConstCVarExpression(const cvarlang::IntermediateCondition* intermediateCondition, Condition& condition, std::list<CVar>& cvars) {
		CVar lhs(intermediateCondition->lhsType, String("___TEMP_CVAR___"), false, intermediateCondition->lhs);
		CVar rhs(intermediateCondition->rhsType, String("___TEMP_CVAR___"), false, intermediateCondition->rhs);

		generateCondition(intermediateCondition, condition, lhs, rhs);
	}
	void CVarCompiler::generateCVarConstExpression(const cvarlang::IntermediateCondition* intermediateCondition, Condition& condition, std::list<CVar>& cvars) {
		CVar& lhs = *std::find_if(cvars.begin(), cvars.end(), [&intermediateCondition](const CVar& cvar) {
			return cvar.getName() == intermediateCondition->lhs;
		});

		CVar rhs(intermediateCondition->rhsType, String("___TEMP_CVAR___"), false, intermediateCondition->rhs);

		generateCondition(intermediateCondition, condition, lhs, rhs);
	}
	void CVarCompiler::generateConstCVarBoolExpression(const cvarlang::IntermediateCondition* intermediateCondition, Condition& condition, std::list<CVar>& cvars) {
		CVar lhs(intermediateCondition->lhsType, String("___TEMP_CVAR___"), false, intermediateCondition->lhs);

		CVar& rhs = *std::find_if(cvars.begin(), cvars.end(), [&intermediateCondition](const CVar& cvar) {
			return cvar.getName() == intermediateCondition->rhs;
		});

		generateCondition(intermediateCondition, condition, lhs, rhs);
	}
	void CVarCompiler::generateConstBoolConstExpression(const cvarlang::IntermediateCondition* intermediateCondition, Condition& condition, std::list<CVar>& cvars) {
		if (intermediateCondition->lhsIsConst) {
			CVar lhs(intermediateCondition->lhsType, String("___TEMP_CVAR___"), false, intermediateCondition->lhs);
			CVar rhs(intermediateCondition->lhsType, String("___TEMP_CVAR___"));

			condition = [&lhs, &rhs]() {
				return lhs >= rhs;
			};
		}
	}

	void CVarCompiler::generateCondition(const cvarlang::IntermediateCondition* intermediateCondition, Condition& condition, CVar& lhs, CVar& rhs) {
		if (intermediateCondition->conditionalOperator == cvarlang::ConditionalOperators::Equal) {
			condition = [&lhs, &rhs]() {
				return lhs == rhs;
			};
		}
		else if (intermediateCondition->conditionalOperator == cvarlang::ConditionalOperators::NotEqual) {
			condition = [&lhs, &rhs]() {
				return lhs != rhs;
			};
		}
		else if (intermediateCondition->conditionalOperator == cvarlang::ConditionalOperators::Smaller) {
			condition = [&lhs, &rhs]() {
				return lhs < rhs;
			};
		}
		else if (intermediateCondition->conditionalOperator == cvarlang::ConditionalOperators::SmallerOrEqual) {
			condition = [&lhs, &rhs]() {
				return lhs <= rhs;
			};
		}
		else if (intermediateCondition->conditionalOperator == cvarlang::ConditionalOperators::Greater) {
			condition = [&lhs, &rhs]() {
				return lhs > rhs;
			};
		}
		else if (intermediateCondition->conditionalOperator == cvarlang::ConditionalOperators::GreaterOrEqual) {
			condition = [&lhs, &rhs]() {
				return lhs >= rhs;
			};
		}
	}

	void CVarCompiler::compile(std::list<CVarFile>& files, std::list<CVar>& cvars, std::list<CVarRecord>& records, const bool synced) {
		this->synced = synced;

		// Generate tokens from lines.
		CVarTokenizer tokenizer;

		std::list<CVarToken> tokens;
		tokenizer.tokenize(files, tokens);

		if (tokenizer.hasErrors()) {
			copyErrors(&tokenizer);

			return;
		}

		generateCVars(cvars, records, tokens);
	}

	CVarCompiler::~CVarCompiler() {
	}
}