#include "sani/platform/binary_reader.hpp"
#include "sani/platform/file_system.hpp"
namespace sani {
	namespace io {

		BinaryReader::BinaryReader() 
			: fs(nullptr), file("") {

		}
		BinaryReader::BinaryReader(const FileSystem* fs, const String& file) 
			: fs(fs), file(file) {

		}

		BinaryReader::~BinaryReader() {}

		int16 BinaryReader::readInt16() {
			return static_cast<int16>(readUint16());
		}
		int32 BinaryReader::readInt32() {
			return static_cast<int32>(readUint32());
		}
		int64 BinaryReader::readInt64() {
			return static_cast<int64>(readUint64());
		}

		uint16 BinaryReader::readUint16() {
			uint8 b1 = readByte();
			uint8 b2 = readByte();
			return uint16(b1) | uint16(b2) << 8;
		}
		uint32 BinaryReader::readUint32() {
			uint8 b1 = readByte();
			uint8 b2 = readByte();
			uint8 b3 = readByte();
			uint8 b4 = readByte();
			return uint32(b1) | uint32(b2) << 8 |
				uint32(b3) << 16 | uint32(b4) << 24;
		}
		uint64 BinaryReader::readUint64() {
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

		char BinaryReader::readChar() {
			return static_cast<char>(readByte());
		}

		uint8 BinaryReader::readByte() {
			return fs->readByte(file);
		}

		float32 BinaryReader::readSingle() {
			uint32 val = readUint32();
			return *(float*)&val;
		}

		float64 BinaryReader::readDouble() {
			uint64 val = readUint64();
			return *(double*)&val;
		}

		// TODO does this need to be null terminated?
		String BinaryReader::readString() {
			uint64 size = read7BitEncodedInt();
			String str;
			str.reserve(static_cast<uint32>(size));
			size_t index = 0;
			while (index++ < size) {
				str.append(1, readChar());
			}
			return str;
		}

		uint64 BinaryReader::read7BitEncodedInt() {
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