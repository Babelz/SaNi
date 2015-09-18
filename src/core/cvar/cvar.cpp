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
		value = stringVal;
	}
	void CVar::read(int32& value) const {
		value = int32Val;
	}
	void CVar::read(float32& value) const {
		value = float32Val;
	}
	void CVar::read(float64& value) const {
		value = float64Val;
	}

	void CVar::write(const String& value) {
		stringVal = value; changed = true;
	}
	void CVar::write(int32 value) {
		int32Val = value; changed = true;
	}
	void CVar::write(float32 value) {
		float32Val = value; changed = true;
	}
	void CVar::write(float64 value) {
		float64Val = value; changed = true;
	}

	CVar::~CVar() {
	}
}