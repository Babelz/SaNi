#pragma once
#include "sani/platform/file.hpp"
namespace sani {
	namespace io {
		class FileStream {
		private:
			const String filePath;
			const Filemode mode;
		public:
			FileStream(const String& filePath, const Filemode mode = Filemode::Read);
			~FileStream();
			// disable copying
			FileStream(const FileStream& fileStream) = delete;
			FileStream(FileStream&& fileStream) = delete;
			FileStream& operator =(const FileStream& fileStream) = delete;
			FileStream& operator =(FileStream&& fileStream) = delete;

			/// Reads the data from current position
			///
			/// @param buffer The buffer where to read 
			/// @param size The amount of bytes to read
			/// @return The bytes how much was read
			int64 read(unsigned char* buffer, const int32 size) const;

			uint32 write(const unsigned char* data, const int32 size) const;

			void seek(const void* seekpos, const int64 offset) const;
		};
	}
}