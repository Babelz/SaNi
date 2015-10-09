#pragma once 
#include "sani/types.hpp"
#include "sani/forward_declare.hpp"

SANI_FORWARD_DECLARE_2(sani, io, FileStream);
namespace sani {
	namespace io {
		class BinaryReader {
		private:
			const FileStream* stream;
		public:
			BinaryReader(const FileStream* stream);
			virtual ~BinaryReader();
			int16 readInt16();
			int32 readInt32();
			int64 readInt64();

			uint16 readUint16();
			uint32 readUint32();
			uint64 readUint64();

			float32 readSingle();

			String readString();
			float64 readDouble();

			uint8 readByte();
			char readChar();
			uint64 read7BitEncodedInt();

		};
	}
}
