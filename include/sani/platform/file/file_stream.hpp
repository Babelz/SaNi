#pragma once
#include "sani/platform/file/file.hpp"
#include "sani/platform/platform_config.hpp"
#include "sani/types.hpp"

namespace sani {
	namespace io {

		/// Specifies how the operating system should open a file
		enum class Filemode : uint32 {
			/// Read only
			Read = 1 << 0,
			/// Write only
			Write = 1 << 1,
			/// Overwrite
			Truncate = 1 << 2
		};

		enum class SeekPosition : uint32 {
			/// From begin
			Begin = 0,
			/// From current position
			Current = 1,
			/// From end
			End = 2
		};

		/// Operator for bitwise or
		inline Filemode operator|(const Filemode a, const Filemode b) {
			return static_cast<Filemode>(static_cast<uint32>(a) | static_cast<uint32>(b));
		}

		class FileStream {
		protected:
			const String filePath;
			const Filemode mode;
		public:
			
			FileStream(const String& filePath, const Filemode mode);
			virtual ~FileStream();
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
			virtual int64 read(unsigned char* buffer, const int32 size) const = 0;

			/// Reads the data from offset position
			///
			/// @param buffer The buffer where to read 
			/// @param offset Where to seek
			/// @param size The amount of bytes to read
			/// @return The bytes how much was read
			virtual int64 read(unsigned char* buffer, const int32 offset, const int32 size) const = 0;

			/// Writes the data to file
			/// 
			/// @param data The data that needs to be written
			/// @param size The size of the data measured in bytes
			/// @return The bytes written
			virtual uint32 write(const unsigned char* data, const int32 size) const = 0;

			/// Seeks in the file stream
			///
			/// @param seekpos What position is used as the origin
			/// @param offset How many bytes are traversed
			virtual void seek(const SeekPosition seekpos, const long offset) const = 0;

			inline Filemode getOpenMode() const;
			inline const String& getPath() const;

			/// Flushs the file stream
			virtual void flush() const = 0;
		};

		namespace priv {
			class _FileStream : public sani::io::FileStream {
			private:
				FILE* handle;
			public:
				_FileStream(const String& filePath, const Filemode mode, FILE* handle);
				~_FileStream();
				virtual int64 read(unsigned char* buffer, const int32 size) const;
				virtual int64 read(unsigned char* buffer, const int32 offset, const int32 size) const;
				virtual uint32 write(const unsigned char* data, const int32 size) const;
				virtual void seek(const SeekPosition seekpos, const long offset) const;
				virtual void flush() const;
			};
		}
	}
}

#include "inl/file_stream.inl"