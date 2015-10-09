#pragma once

#include "sani/forward_declare.hpp"
#include "sani/types.hpp"
#include <list>

namespace sani {

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
		const String configurationRootFolder;
		io::FileSystem& fileSystem;
	public:
		CVarLoader(const String& configurationRootFolder, io::FileSystem& fileSystem);

		/// Loads all cvar files found from the configuration root folder.
		/// @param[in] files list in which the files will be loaded
		void load(std::list<CVarFile>& files) const;

		~CVarLoader();
	};
}