#include "sani/core/cvar/cvar_loader.hpp"
#include "sani/core/cvar/cvar_file.hpp"
#include "sani/platform/file/file_system.hpp"

namespace sani {

	CVarLoader::CVarLoader(const String& configurationRootFolder, io::FileSystem& fileSystem) : configurationRootFolder(configurationRootFolder),
																								fileSystem(fileSystem) {
	}

	void CVarLoader::load(std::list<CVarFile>& files) const {
		// TODO: only looks from the root. 
		//		 Once file system can list directories, 
		//		 fix this.

		// Get all the files from the root.
		std::vector<String, std::allocator<String>> cvarFiles;
		fileSystem.listFiles(cvarFiles, configurationRootFolder);

		// Read lines and save paths.
		for (String& filename : cvarFiles) {

			// Check if the file is a .cfg, if not, don't parse it.
			const String ending(".cfg");

			if (filename.substr(filename.size() - ending.size(), ending.size()) == ending) {
				// Open files.
				const String path(configurationRootFolder + "\\" + filename);

				if (!fileSystem.isFileOpen(path)) fileSystem.openFile(path, io::Filemode::Read);

				// Just assume the file is open.
				const String contents(fileSystem.getFileDataString(path));

				// Create new file record from the data collected.
				files.push_back(CVarFile(path, contents));

				// Close after reading.
				fileSystem.closeFile(path);
			}
		}
	}

	CVarLoader::~CVarLoader() {
	}
}