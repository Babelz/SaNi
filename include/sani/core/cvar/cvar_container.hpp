#pragma once

#include "sani/core/cvar/cvar_record.hpp"
#include "sani/core/cvar/cvar.hpp"
#include <list>

namespace sani {

	// TODO: implement.

	class CVarContainer {
	private:
		std::list<CVar> cvars;
	public:
		CVarContainer(const std::list<CVar>&& cvars);

		bool contains(const String& name);
		CVar& find(const String& name);

		~CVarContainer();

		CVarContainer& operator =(CVarContainer& other) = delete;
		CVarContainer& operator = (CVarContainer&& other) = delete;
		CVarContainer(CVarContainer& other) = delete;
	};
}