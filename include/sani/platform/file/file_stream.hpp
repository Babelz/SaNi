#pragma once
#include "sani/platform/file/file.hpp"
#include "sani/platform/platform_config.hpp"

namespace sani {
	namespace io {

		/// Specifies how the operating system should open a file
		enum Filemode {
			/// Read only
			Read = 1 << 0,
			/// Write only
			Write = 1 << 1,
			/// Overwrite
			Truncate = 1 << 2
		};

		enum SeekPosition {
			/// From begin
			Begin,
			/// From current position
			Current,
			/// From end
			End
		};

		/// Operator for bitwise or
		inline Filemode operator|(Filemode a, Filemode b) {
			return static_cast<Filemode>(static_cast<int>(a) | static_cast<int>(b));
		}

		class FileStream {
		private:
			const String filePath;
			const Filemode mode;
			FILE* handle;
		public:
			FileStream(const String& filePath, const Filemode mode, FILE* handle);
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

			/// Reads the data from offset position
			///
			/// @param buffer The buffer where to read 
			/// @param offset Where to seek
			/// @param size The amount of bytes to read
			/// @return The bytes how much was read
			int64 read(unsigned char* buffer, const int32 offset, const int32 size) const;

			/// Writes the data to file
			/// 
			/// @param data The data that needs to be written
			/// @param size The size of the data measured in bytes
			/// @return The bytes written
			uint32 write(const unsigned char* data, const int32 size) const;

			/// Seeks in the file stream
			///
			/// @param seekpos What position is used as the origin
			/// @param offset How many bytes are traversed
			void seek(const SeekPosition seekpos, const long offset) const;
		};
	}
}