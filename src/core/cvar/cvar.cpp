#include "sani/core/cvar/cvar.hpp"

namespace sani {

	CVar::CVar(const CVarRequireStatement& statement, const cvarlang::ValueType type, 
			   const String& name, const bool synced, const String& value) : statement(statement),
																			 type(type),
																			 name(name),
																		     synced(synced),
																			 changed(false),
																			 stringVal(value) {
	}

	CVar::CVar(const CVarRequireStatement& statement, const cvarlang::ValueType type,
			   const String& name, const bool synced, const int32 value) : statement(statement),
																		   type(type),
																		   name(name),
																		   synced(synced),
																		   changed(false),
																		   int32Val(value) {
	}

	CVar::CVar(const CVarRequireStatement& statement, const cvarlang::ValueType type,
			   const String& name, const bool synced, const float32 value) : statement(statement),
																			 type(type),
																			 name(name),
																			 synced(synced),
																			 changed(false),
																			 float32Val(value) {
	}

	CVar::CVar(const CVarRequireStatement& statement, const cvarlang::ValueType type,
			   const String& name, const bool synced, const float64 value) : statement(statement),
																			 type(type),
																			 name(name),
																			 synced(synced),
																			 changed(false),
																			 float64Val(value) {
	}

	cvarlang::ValueType CVar::getType() const {
		return type;
	}
	const String& CVar::getName() const {
		return name;
	}

	bool CVar::canWrite() const {
		return statement();
	}
	
	bool CVar::hasChanged() const {
		return changed;
	}
	bool CVar::isSynced() const {
		return synced;
	}

	void CVar::read(String& value) const {
		if (type != cvarlang::ValueType::StringVal) return;

		value = stringVal;
	}
	void CVar::read(int32& value) const {
		if (type != cvarlang::ValueType::IntVal) return;

		value = int32Val;
	}
	void CVar::read(float32& value) const {
		if (type != cvarlang::ValueType::FloatVal) return;

		value = float32Val;
	}
	void CVar::read(float64& value) const {
		if (type != cvarlang::ValueType::DoubleVal) return;

		value = float64Val;
	}

	void CVar::write(const String& value) {
		if (type != cvarlang::ValueType::StringVal) return;

		stringVal = value;
		changed = true;
	}
	void CVar::write(int32 value) {
		if (type != cvarlang::ValueType::IntVal) return;

		int32Val = value; 
		changed = true;
	}
	void CVar::write(float32 value) {
		if (type != cvarlang::ValueType::FloatVal) return;

		float32Val = value; 
		changed = true;
	}
	void CVar::write(float64 value) {
		if (type != cvarlang::ValueType::DoubleVal) return;

		float64Val = value; 
		changed = true;
	}

	CVar::~CVar() {
	}
}