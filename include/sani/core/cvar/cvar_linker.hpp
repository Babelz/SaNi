#pragma once

#include "sani/precompiled.hpp"
#include <list>
#include <stack>

namespace sani {

	// Defs.
	typedef std::stack<String> ErrorBuffer;

	// Forwards.
	class CVarFile;
	class LinkRecord;

	/// @class CVarLinker cvar_linker.hpp "sani/core/cvar/cvar_linker.hpp"
	/// @author voidbab
	///
	/// Class that will look for the include keyword and "links" the files.
	/// Will also do recursive linkage checking.
	class CVarLinker {
	private:
		ErrorBuffer errorBuffer;

		void pushError(const String& error);
	public:
		CVarLinker();
		
		bool hasErrors() const;
		String getNextError();

		/// Links the given files.
		void link(std::list<CVarFile>& files);
		
		~CVarLinker();
	};
}