#pragma once

#include "sani/platform/file/file_stream.hpp"
#include "sani/engine/engine_service.hpp"
#include "sani/forward_declare.hpp"

#include <vector>

SANI_FORWARD_DECLARE_2(sani, io, FileSystem);

namespace sani{

	namespace engine {
		
		/// @class FileSystemService file_system_service.hpp "sani/engine/services.hpp"
		/// @author voidbab/siquel?
		///
		/// Service that provides interface for platform independent 
		/// file operations.
		class FileSystemService : public EngineService {
		private:
			io::FileSystem* fileSystem;
		protected:
			void onInitialize() override;
		public:
			FileSystemService(SaNiEngine* const engine);

			bool fileExists(const String& path) const;
			bool isFileOpen(const String& path) const;

			bool openFile(const String& path, const io::Filemode mode, io::FileStream** stream);
			void closeFile(const String& path);

			bool isAbsolutePath(const String& path) const;

			uint32 getFileSize(const String& path) const;

			unsigned char* getFileData(const String& path, int64& fileSize, bool nullTerminate = false) const;
			String getFileDataString(const String& path) const;

			void listFiles(std::vector<String>& files, const String& path) const;

			~FileSystemService() override;
		};
	}
}