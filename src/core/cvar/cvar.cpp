#include "sani/core/cvar/cvar.hpp"

namespace sani {

	CVar::CVar(const cvarlang::ValueType type, const String& name, const bool synced, const String& value) : type(type),
																										     name(name),
																											 synced(synced),
																											 changed(false) {
		initialize(value);
	}

	CVar::CVar(const std::list<CVarRequireStatement>& statements, const cvarlang::ValueType type,
			   const String& name, const bool synced, const String& value) : statements(statements),
																			 type(type),
																			 name(name),
																			 synced(synced),
																			 changed(false) {
		initialize(value);
	}

	CVar::CVar(const cvarlang::ValueType type, const String& name) : type(type),
																	 name(name),
																	 synced(false),
																	 changed(false) {
		// Do default initialization.
		String value = type != cvarlang::ValueType::StringVal ? String("0") : String("");

		initialize(value);
	}

	void CVar::initialize(const String& value) {
		if		(type == cvarlang::ValueType::StringVal)	stringVal = value;
		else if (type == cvarlang::ValueType::IntVal)		int32Val = std::atoi(value.c_str());
		else if (type == cvarlang::ValueType::FloatVal)		float32Val = static_cast<float32>(std::atof(value.c_str()));
		else if (type == cvarlang::ValueType::DoubleVal)	float64Val = std::atof(value.c_str());
	}

	cvarlang::ValueType CVar::getType() const {
		return type;
	}
	const String& CVar::getName() const {
		return name;
	}

	bool CVar::canWrite() const {
		if (statements.size() == 0) return true;

		for (const CVarRequireStatement& statement : statements) if (!statement()) return false;
 		
		return true;
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

	/*
		TODO: could fix these with some delegation...
	*/

	const bool CVar::operator == (const CVar& other) const {
		if (type == cvarlang::ValueType::StringVal) {
			String val(""); other.read(val);

			return stringVal == val;
		}
		else if (type == cvarlang::ValueType::IntVal) {
			int32 val = 0; other.read(val);

			return int32Val == val;
		}
		else if (type == cvarlang::ValueType::FloatVal) {
			float val = 0.0f; other.read(val);

			return float32Val == val;
		}
		else if (type == cvarlang::ValueType::DoubleVal) {
			float64 val = 0.0; other.read(val);

			return float64Val == val;
		}

		return false;
	}
	const bool CVar::operator != (const CVar& other) const {
		return !(*this == other);
	}
	const bool CVar::operator < (const CVar& other) const {
		if (type == cvarlang::ValueType::StringVal) {
			String val(""); other.read(val);

			return stringVal.size() < val.size();
		}
		else if (type == cvarlang::ValueType::IntVal) {
			int32 val = 0; other.read(val);

			return int32Val < val;
		}
		else if (type == cvarlang::ValueType::FloatVal) {
			float val = 0.0f; other.read(val);

			return float32Val < val;
		}
		else if (type == cvarlang::ValueType::DoubleVal) {
			float64 val = 0.0; other.read(val);

			return float64Val < val;
		}

		return false;
	}
	const bool CVar::operator <= (const CVar& other) const {
		if (type == cvarlang::ValueType::StringVal) {
			String val(""); other.read(val);

			return stringVal.size() <= val.size();
		}
		else if (type == cvarlang::ValueType::IntVal) {
			int32 val = 0; other.read(val);

			return int32Val <= val;
		}
		else if (type == cvarlang::ValueType::FloatVal) {
			float val = 0.0f; other.read(val);

			return float32Val <= val;
		}
		else if (type == cvarlang::ValueType::DoubleVal) {
			float64 val = 0.0; other.read(val);

			return float64Val <= val;
		}

		return false;
	}
	const bool CVar::operator > (const CVar& other) const {
		if (type == cvarlang::ValueType::StringVal) {
			String val(""); other.read(val);

			return stringVal.size() > val.size();
		}
		else if (type == cvarlang::ValueType::IntVal) {
			int32 val = 0; other.read(val);

			return int32Val > val;
		}
		else if (type == cvarlang::ValueType::FloatVal) {
			float val = 0.0f; other.read(val);

			return float32Val > val;
		}
		else if (type == cvarlang::ValueType::DoubleVal) {
			float64 val = 0.0; other.read(val);

			return float64Val > val;
		}

		return false;
	}
	const bool CVar::operator >= (const CVar& other) const {
		if (type == cvarlang::ValueType::StringVal) {
			String val(""); other.read(val);

			return stringVal.size() >= val.size();
		}
		else if (type == cvarlang::ValueType::IntVal) {
			int32 val = 0; other.read(val);

			return int32Val >= val;
		}
		else if (type == cvarlang::ValueType::FloatVal) {
			float val = 0.0f; other.read(val);

			return float32Val >= val;
		}
		else if (type == cvarlang::ValueType::DoubleVal) {
			float64 val = 0.0; other.read(val);

			return float64Val >= val;
		}

		return false;
	}
}