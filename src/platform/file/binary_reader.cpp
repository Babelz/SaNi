#include "sani/platform/file/binary_reader.hpp"
#include "sani/platform/file/file_stream.hpp"
#include <stdexcept>
namespace sani {
	namespace io {

		BinaryReader::BinaryReader(const FileStream* stream) 
			: stream(stream) {
			//assert(stream->)
		}

		BinaryReader::~BinaryReader() {}

		int16 BinaryReader::readInt16() const {
			return static_cast<int16>(readUint16());
		}
		int32 BinaryReader::readInt32() const {
			return static_cast<int32>(readUint32());
		}
		int64 BinaryReader::readInt64() const {
			return static_cast<int64>(readUint64());
		}

		uint16 BinaryReader::readUint16() const {
			uint8 b1 = readByte();
			uint8 b2 = readByte();
			return uint16(b1) | uint16(b2) << 8;
		}
		uint32 BinaryReader::readUint32() const {
			uint8 b1 = readByte();
			uint8 b2 = readByte();
			uint8 b3 = readByte();
			uint8 b4 = readByte();
			return uint32(b1) | uint32(b2) << 8 |
				uint32(b3) << 16 | uint32(b4) << 24;
		}
		uint64 BinaryReader::readUint64() const {
			uint8 b1 = readByte();
			uint8 b2 = readByte();
			uint8 b3 = readByte();
			uint8 b4 = readByte();
			uint8 b5 = readByte();
			uint8 b6 = readByte();
			uint8 b7 = readByte();
			uint8 b8 = readByte();
			return uint64(b1) | uint64(b2) << 8 |
				uint64(b3) << 16 | uint64(b4) << 24 |
				uint64(b5) << 32 | uint64(b6) << 40 |
				uint64(b7) << 48 | uint64(b8) << 56;
		}

		char BinaryReader::readChar() const {
			return static_cast<char>(readByte());
		}

		uint8 BinaryReader::readByte() const {
			unsigned char buffer[1];
			stream->read(buffer, 1);
			return static_cast<uint8>(buffer[0]);
		}

		float32 BinaryReader::readSingle() const  {
			uint32 val = readUint32();
			return *(float*)&val;
		}

		float64 BinaryReader::readDouble() const  {
			uint64 val = readUint64();
			return *(double*)&val;
		}

		// TODO does this need to be null terminated?
		String BinaryReader::readString() const {
			uint64 size = read7BitEncodedInt();
			String str;
			str.reserve(static_cast<uint32>(size));
			size_t index = 0;
			while (index++ < size) {
				str.append(1, readChar());
			}
			return str;
		}

		uint64 BinaryReader::read7BitEncodedInt() const {
			uint64 buffer = 0;
			int index = 0;
			uint8 current = 0;
			
			do {
				if (index++ == 8)
					throw std::runtime_error("Could not read variable-length quantity from provided stream");
				buffer <<= 7;
				current = readByte();
				buffer |= (current & 0x7Fu);
			} while ((current & 0x80) != 0);

			return buffer;
		}
	}
}