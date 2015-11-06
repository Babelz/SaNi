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
			int16 readInt16() const;
			int32 readInt32() const;
			int64 readInt64() const;

			uint16 readUint16() const;
			uint32 readUint32() const;
			uint64 readUint64() const;

			float32 readSingle() const;

			String readString() const;
			float64 readDouble() const;

			uint8 readByte() const;
			char readChar() const;
			uint64 read7BitEncodedInt() const;

		};
	}
}
