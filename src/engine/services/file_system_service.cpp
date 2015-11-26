#include "sani/engine/services/file_system_service.hpp"
#include "sani/platform/file/file_system.hpp"

namespace sani {

	namespace engine {

		FileSystemService::FileSystemService(SaNiEngine* const engine) : EngineService("file system", engine) {
		}

		bool FileSystemService::onInitialize() {
			fileSystem = new io::FileSystem();

			return true;
		}

		bool FileSystemService::fileExists(const String& path) const {
			return fileSystem->fileExists(path);
		}
		bool FileSystemService::isFileOpen(const String& path) const {
			return fileSystem->isFileOpen(path);
		}

		bool FileSystemService::openFile(const String& path, const io::Filemode mode, io::FileStream** stream) {
			return fileSystem->openFile(path, mode, stream);
		}
		void FileSystemService::closeFile(const String& path)  {
			fileSystem->closeFile(path);
		}

		bool FileSystemService::isAbsolutePath(const String& path) const  {
			return fileSystem->isAbsolutePath(path);
		}

		uint32 FileSystemService::getFileSize(const String& path) const  {
			return fileSystem->getFileSize(path);
		}

		unsigned char* FileSystemService::getFileData(const String& path, int64& fileSize, bool nullTerminate = false) const  {
			return fileSystem->getFileData(path, fileSize, nullTerminate);
		}
		String FileSystemService::getFileDataString(const String& path) const  {
			return fileSystem->getFileDataString(path);
		}

		void FileSystemService::listFiles(std::vector<String>& files, const String& path) const {
			return fileSystem->listFiles(files, path);
		}

		FileSystemService::~FileSystemService() {
			delete fileSystem;
		}
	}
}