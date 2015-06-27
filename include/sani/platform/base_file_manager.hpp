#pragma once

#include "sani/precompiled.hpp"
#include "sani/platform/file.hpp"
#include <vector>
#include <map>
#include <unordered_map>

namespace sani {
	namespace io {

		/// @class BaseFileManager base_file_manager.hpp "sani/platform/base_file_manager.hpp"
		/// @author siquel
		/// 
		/// Helper for file access
		class BaseFileManager {		
		public:
			/// Default constructor
			BaseFileManager();
			/// Default deconstructor
			virtual ~BaseFileManager();

			/// Checks if the file exists
			/// @param[in] path The path where the file should be
			/// @returns true if the file exists, false if it does not exist
			virtual bool fileExists(const String& path) const = 0;

			/// Checks if the file is opened for reading/writing
			/// @param[in] path File path
			/// @returns true if the file is opened, false if it isn't
			virtual bool isFileOpen(const String& path) const = 0;

			/// Opens file for operations
			/// @param[in] path The file path
			/// @param[in] mode The mode how file should be opened
			/// @returns true if the file opening succeeded, otherwise false
			virtual bool openFile(const String& path, const Filemode mode) = 0;

			/// Closes the file in path
			/// @param[in] path File path
			virtual void closeFile(const String& path) = 0;

			/// Utility for checking if path is absolute path
			/// @param[in] path The path string which needs to be checked
			virtual bool isAbsolutePath(const String& path) const;

			/// Gets the size of the file in bytes
			/// @param[in] path File path
			/// @warning If there isn't file handle opened to this path, it will be opened and then closed
			virtual size_t getFileSize(const String& path) const = 0;

			/// Reads the file into buffer
			/// @param[in] path The file path to the file
			/// @param[out] fileSize How many bytes were read
			/// @param[in] nullTerminate Should the buffer be null terminated
			virtual unsigned char* getFileData(const String& path, size_t& fileSize, bool nullTerminate = false) const = 0;

			/// Reads the file into string
			/// @param[in] path File path to the file
			virtual String getFileDataString(const String& path) const = 0;
			
			unsigned char getByte();

			virtual void getBytes(std::vector<unsigned char>& out, const String& path, size_t offset, size_t count) const = 0;

			virtual void listFiles(std::vector<String>& files, const String& path) const = 0;
		};
	}
}
