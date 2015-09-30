#include "sani/platform/file/binary_writer.hpp"
#include "sani/platform/file/file_system.hpp"

namespace sani {
	namespace io {
		BinaryWriter::BinaryWriter() {}

		BinaryWriter::BinaryWriter(FILE* fptr)
			: file(fptr) {}

		BinaryWriter::~BinaryWriter() {}

		void BinaryWriter::write(uint8 value) {
			fwrite((unsigned char*)&value, sizeof(uint8), 1, file);
		}

		void BinaryWriter::write(uint16 value) {
			fwrite((unsigned char*)&value, sizeof(uint16), 1, file);
		}

		void BinaryWriter::write(uint32 value) {
			fwrite((unsigned char*)&value, sizeof(uint32), 1, file);
		}

		void BinaryWriter::write(uint64 value) {
			fwrite((unsigned char*)&value, sizeof(uint64), 1, file);
		}

		void BinaryWriter::write(int8 value) {
			fwrite((unsigned char*)&value, sizeof(int8), 1, file);
		}

		void BinaryWriter::write(int16 value) {
			fwrite((unsigned char*)&value, sizeof(int16), 1, file);
		}

		void BinaryWriter::write(int32 value) {
			fwrite((unsigned char*)&value, sizeof(int32), 1, file);
		}

		void BinaryWriter::write(int64 value) {
			fwrite((unsigned char*)&value, sizeof(int64), 1, file);
		}

		void BinaryWriter::write(float32 value) {
			fwrite((unsigned char*)&value, sizeof(float32), 1, file);
		}

		void BinaryWriter::write(float64 value) {
			fwrite((unsigned char*)&value, sizeof(float64), 1, file);
		}

		void BinaryWriter::write(const String& value) {
			write7BitEncodedInt(value.size());
			fwrite(value.c_str(), sizeof(char), value.size(), file);
		}

		void BinaryWriter::write7BitEncodedInt(uint64 value) {
			
			int index = 3;
			bool reached = false;
			uint64 mask = 0x7Fu << (index * 7);
			while (index >= 0) {
				uint64 val = (mask & value);
				if (val > 0 || reached) {
					reached = true;
					val >>= index * 7;
					if (index > 0)
						val |= 0x80;
					uint8 asd = (uint8)val;
					fwrite((unsigned char*)&asd, sizeof(uint8), 1, file);
				}
				mask >>= 7;
				--index;
			}
			if (!reached && index < 0) {
				fwrite('\0', sizeof(char), 1, file);
			}
		}
	}
}