#pragma once

#include "sani/precompiled.hpp"
#include <vector>
#include <map>
#include <unordered_map>

SANI_FORWARD_DECLARE_2(sani, io, File);

namespace sani {
	namespace io {
		enum Filemode;

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
			/// @param[in] file Pointer to file
			/// @returns true if the file is opened, false if it isn't
			virtual bool isFileOpen(const File* file) const = 0;

			/// Opens file for operations
			/// @param[out] file Pointer to file where the opened while should be assigned
			/// @param[in] path The file path
			/// @param[in] mode The mode how file should be opened
			/// @returns true if the file opening succeeded, otherwise false
			virtual bool openFile(File** file, const String& path, const Filemode mode) = 0;

			/// Closes the file and deletes the pointer
			/// @param[in] file The file which should be closed
			/// @warning The file pointer is deleted and becomes invalid
			virtual void closeFile(File* file) = 0;

			/// Utility for checking if path is absolute path
			/// @param[in] path The path string which needs to be checked
			virtual bool isAbsolutePath(const String& path) const;

			/// Gets the size of the file in bytes
			/// @param[in] path File path
			/// @warning If there isn't file handle opened to this path, it will be opened and then closed
			virtual size_t getFileSize(const String& path) const = 0;

			/// Gets the size of the file in bytes
			/// @param[in] file The file pointer
			/// @warning If there isn't file handle opened to this path, it will be opened and then closed
			virtual size_t getFileSize(const File* file) const = 0;

			/// Reads the file into buffer
			/// @param[in] file Pointer to file which should be read
			/// @param[out] fileSize How many bytes were read
			/// @param[in] nullTerminate Should the buffer be null terminated
			virtual unsigned char* getFileData(const File* file, size_t& fileSize, bool nullTerminate = false) const = 0;

			/// Reads the file into string
			/// @param[in] file Pointer to file which should be read
			virtual String getFileDataString(const File* file) const = 0;
			
			unsigned char getByte();

			virtual void getBytes(std::vector<unsigned char>& out, const File* file, size_t offset, size_t count) const = 0;
		};
	}
}
