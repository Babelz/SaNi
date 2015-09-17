#pragma once

#include "sani/forward_declare.hpp"
#include "sani/precompiled.hpp"
#include <list>

namespace sani {
	
	const String ConfigurationRootFolder = "/configuration/";

	// Forwards.
	SANI_FORWARD_DECLARE_1(io, FileSystem);
	class CVarFile;

	/// @class CVarLoader cvar_loader.hpp "sani/core/cvar/cvar_loader.hpp"
	/// @author voidbab
	/// 
	/// Class thath is responsible for finding and loading all 
	/// CVar files from the configuration folder.
	class CVarLoader {
	private:
		io::FileSystem& fileSystem;
	public:
		CVarLoader(io::FileSystem& fileSystem);

		/// Loads all cvar files found from the configuration root folder.
		/// @param[in] files list in which the files will be loaded
		void load(std::list<CVarFile>& files) const;

		~CVarLoader();
	};
}