#include "sani/platform/platform_config.hpp"
#if SANI_TARGET_PLATFORM == SANI_PLATFORM_ANDROID
#include <cassert>
#include <stdexcept>
#include "sani/platform/file/file_system.hpp"
#include <sys/stat.h>
#include <dirent.h>
#include "sani/platform/platform_exception.hpp"
#include "sani/platform/file/android/file_stream_android.hpp"
namespace sani {
	namespace io {
		void FileSystem::setAssetManager(AAssetManager* assetmanager) {
			androidAssetManager = assetmanager;
		}

		bool FileSystem::isAbsolutePath(const String& path) const  {
			// android absolute paths can be /foo/bar or assets (which is inside apk)
			if (path.empty()) return false;

			String prefix("assets/");
			// if the path starts with assets/, its absolute path inside APK
			if (std::equal(prefix.begin(), prefix.end(), path.begin())) return true;

			// same as in unix, like /data/asd or /sdcard/data
			return path.at(0) == '/';
		}

		bool FileSystem::isFileOpen(const String& path) const {
			return assetHandles.find(path) != assetHandles.end() || handles.find(path) != handles.end();
		}

		bool FileSystem::openFile(const String& path, const Filemode mode, FileStream** stream) {
			if (isFileOpen(path)) return true;


			// apk
			if (path.at(0) != '/') {
				// android doesnt support it..
				if (static_cast<uint32>(mode)& static_cast<uint32>(Filemode::Write) || static_cast<uint32>(mode)& static_cast<uint32>(Filemode::Truncate)) {
					throw sani::UnsupportedOperation("Android does not support writing inside APK");
				}
				String withoutAssets(path.substr(7));
				AAsset* asset = AAssetManager_open(androidAssetManager, withoutAssets.c_str(), AASSET_MODE_UNKNOWN);
				if (!asset) return false;
				
				assetHandles[path] = asset;
				handles[path] = new priv::AndroidFileStream(path, mode, asset);
				*stream = handles[path];
				return true;
			}
			// absolute

			char access[5] = { 0 };

			if (static_cast<uint32>(mode)& static_cast<uint32>(Filemode::Read) && static_cast<uint32>(mode)& static_cast<uint32>(Filemode::Write)) {
				access[0] = 'a'; access[1] = '+';  access[2] = 'b';
			}
			else if (static_cast<uint32>(mode)& static_cast<uint32>(Filemode::Truncate) && static_cast<uint32>(mode)& static_cast<uint32>(Filemode::Read)) {
				access[0] = 'w'; access[1] = '+'; access[2] = 'b';
			}
			else if (static_cast<uint32>(mode)& static_cast<uint32>(Filemode::Truncate)) {
				access[0] = 'w'; access[1] = 'b';
			}
			else if (static_cast<uint32>(mode)& static_cast<uint32>(Filemode::Read)) {
				access[0] = 'r'; access[1] = 'b';
			}
			else if (static_cast<uint32>(mode)& static_cast<uint32>(Filemode::Write)) {
				access[0] = 'a'; access[1] = 'b';
			}
			FILE* handle = nullptr;
			handle = fopen(path.c_str(), access);

			if (!handle) return false;

			handles[path] = new priv::_FileStream(path, mode, handle);
			*stream = handles[path];

			// File open succeeded
			return true;
		}

		void FileSystem::closeFile(const String& path) {
			if (!isFileOpen(path)) return;
			if (path.at(0) != '/') {
				AAsset* asset = assetHandles[path];
				AAsset_close(asset);
				assetHandles.erase(path);
			}
			
			FileStream* handle = handles[path];
			delete handle;
			handle = nullptr;
			handles.erase(path);
			
		}

		unsigned char* FileSystem::getFileData(const String& path, int64& fileSize, bool nullTerminate /*= false*/) const {	
			assert(isFileOpen(path));

			// inside APK
			/*if (path.at(0) != '/') {
				AAsset* asset = assetHandles.at(path);
				if (asset) {
					off_t size = AAsset_getLength(asset);

					unsigned char* buffer;
					if (nullTerminate) {
						buffer = (unsigned char*)malloc(size + 1);
						buffer[size] = '\0';
					}
					else {
						buffer = (unsigned char*)malloc(size);
					}

					int readBytes = AAsset_read(asset, buffer, size);
					if (readBytes != size) {
						if (buffer) {
							free(buffer);
							buffer = nullptr;
						}
						fileSize = 0;
						return nullptr;
					}
					fileSize = readBytes;
					return buffer;

				}
				return nullptr;
			} */
			// absolute path
			
			FileStream* handle = handles.at(path);
			size_t fsize = getFileSize(path);
			unsigned char* buffer = nullptr;
			if (nullTerminate) {
				buffer = (unsigned char*)malloc(fsize + 1);
				buffer[fsize] = '\0';
			}
			else {
				buffer = (unsigned char*)malloc(fsize);
			}
			int64 readBytes = 0;
			try {
				readBytes = handle->read(buffer, fsize);
			}
			catch (std::exception& ex) {
				(void)ex;
				throw;
			}

			// Failed
			if (readBytes != fsize) {
				if (buffer) {
					free(buffer);
					buffer = nullptr;
				}
				fileSize = 0;
				return nullptr;
			}

			// Success
			fileSize = readBytes;
			return buffer;
			
		}

		size_t FileSystem::getFileSize(const String& path) const {

			if (path.empty()) return 0;
			// inside apk
			if (path.at(0) != '/') {
				// file is not open
				if (assetHandles.find(path) == assetHandles.end()) {
					AAsset* asset = AAssetManager_open(androidAssetManager, path.c_str(), AASSET_MODE_UNKNOWN);
					if (asset) {
						size_t size = AAsset_getLength(asset);
						AAsset_close(asset);
						return size;
					}
					// file not found
					return 0;
				}
				// its open
				return AAsset_getLength(assetHandles.at(path));
			}
			// absolute path
			struct stat statbuf;
			if (stat(path.c_str(), &statbuf) == -1) {
				// error
				return 0;
			}
			return statbuf.st_size;
		}

		bool FileSystem::fileExists(const String& path) const {
			if (path.empty()) return false;
			// we need to check if its in asset folder
			if (path.at(0) != '/') {
				AAsset* asset = AAssetManager_open(androidAssetManager, path.c_str(), AASSET_MODE_UNKNOWN);
				// file found
				if (asset) {
					AAsset_close(asset);
					return true;
				}
			} 
			// its absolute path 
			struct stat buffer;
			return (stat(path.c_str(), &buffer) == 0);
		}

		void FileSystem::listFiles(std::vector<String>& files, const String& path) const {

			if (path.at(0) != '/') {
				AAssetDir* aa = AAssetManager_openDir(androidAssetManager, path.c_str());
				const char* filename;
				while ((filename = AAssetDir_getNextFileName(aa))) {
					files.push_back(filename);
				}
				AAssetDir_close(aa);
			}
			else {
				DIR *d;
				struct dirent* dir;
				d = opendir(path.c_str());

				if (d) {
					while ((dir = readdir(d)) != NULL) {
						files.push_back(dir->d_name);
					}
					closedir(d);
				}
			}
		}
	}
}

#endif