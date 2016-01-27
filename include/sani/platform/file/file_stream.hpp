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

		class Stream {
		private:
			// disable copying
			Stream(const Stream& stream) = delete;
			Stream(Stream&& stream) = delete;
			Stream& operator =(const Stream& stream) = delete;
			Stream& operator =(Stream&& stream) = delete;
		public:
			Stream() = default;
			virtual ~Stream() = default;
			virtual uint32 read(unsigned char* buffer, const uint32 size) = 0;
			virtual uint32 read(unsigned char* buffer, const int32 offset, const uint32 size) = 0;
			virtual uint32 write(const unsigned char* data, const uint32 size) = 0;
			virtual void seek(const SeekPosition seekpos, const long offset) = 0;
			virtual uint32 size() = 0;
			virtual void flush() = 0;
		};

		class FileStream : public Stream {
		protected:
			const String filePath;
			const Filemode mode;
		public:
			
			FileStream(const String& filePath, const Filemode mode);
			virtual ~FileStream();


			/// Reads the data from current position
			///
			/// @param buffer The buffer where to read 
			/// @param size The amount of bytes to read
			/// @return The bytes how much was read
			virtual uint32 read(unsigned char* buffer, const uint32 size) = 0;

			/// Reads the data from offset position
			///
			/// @param buffer The buffer where to read 
			/// @param offset Where to seek
			/// @param size The amount of bytes to read
			/// @return The bytes how much was read
			virtual uint32 read(unsigned char* buffer, const int32 offset, const uint32 size) = 0;

			/// Writes the data to file
			/// 
			/// @param data The data that needs to be written
			/// @param size The size of the data measured in bytes
			/// @return The bytes written
			virtual uint32 write(const unsigned char* data, const uint32 size) = 0;

			/// Seeks in the file stream
			///
			/// @param seekpos What position is used as the origin
			/// @param offset How many bytes are traversed
			virtual void seek(const SeekPosition seekpos, const long offset) = 0;

			virtual uint32 size() = 0;

			inline Filemode getOpenMode() const;
			inline const String& getPath() const;

			/// Flushs the file stream
			virtual void flush() = 0;
		};

		namespace priv {
			class FileStreamImpl : public sani::io::FileStream {
			private:
				FILE* handle;
			public:
				FileStreamImpl(const String& filePath, const Filemode mode, FILE* handle);
				~FileStreamImpl();
				virtual uint32 read(unsigned char* buffer, const uint32 size) override;
				virtual uint32 read(unsigned char* buffer, const int32 offset, const uint32 size) override;
				virtual uint32 write(const unsigned char* data, const uint32 size) override;
				virtual void seek(const SeekPosition seekpos, const long offset) override;
				virtual void flush() override;
				virtual uint32 size() override;
			};
		}
	}
}

#include "inl/file_stream.inl"