#pragma once

#include "sani/core/cvar/cvar_file.hpp"
#include "sani/types.hpp"
#include <stack>
#include <list>

namespace sani {

	typedef std::stack<String> ErrorBuffer;

	class CVarLinker {
	private:
		ErrorBuffer errorBuffer;

		CVarFile* findFile(const String& fileName, std::list<CVarFile>& files);
		void linkFiles(CVarFile* file, std::list<CVarFile>& files);

		void pushError(const String& message);
	public:
		CVarLinker();

		bool hasErrors() const;
		String getNextError();

		void link(const String& fileName, std::list<CVarFile>& files);

		~CVarLinker();
	};
}