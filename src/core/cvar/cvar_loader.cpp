#include "sani/core/cvar/cvar_loader.hpp"
#include "sani/core/cvar/cvar_file.hpp"
#include "sani/platform/file_system.hpp"

namespace sani {

	CVarLoader::CVarLoader(io::FileSystem& fileSystem) : fileSystem(fileSystem) {
	}

	void CVarLoader::load(std::list<CVarFile>& files) const {
		// TODO: only looks from the root. 
		//		 Once file system can list directories, 
		//		 fix this.

		// Get all the files from the root.
		std::vector<String, std::allocator<String>> cvarFiles;
		fileSystem.listFiles(cvarFiles, ConfigurationRootFolder);

		// Read lines and save paths.
		for (String& filename : cvarFiles) {
			// Open files.
			if (!fileSystem.isFileOpen(filename))  fileSystem.openFile(filename,  io::Filemode::Read);
			
			// Just assume the file is open.
			const String contents = fileSystem.getFileDataString(filename);

			files.push_back(CVarFile(filename, contents));

			// Close after reading.
			fileSystem.closeFile(filename);
		}
	}

	CVarLoader::~CVarLoader() {
	}
}