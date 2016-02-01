#include "sani/platform/file/binary_writer.hpp"
#include "sani/platform/file/file_stream.hpp"

namespace sani {
	namespace io {

		BinaryWriter::BinaryWriter(Stream* stream) : stream(stream) {
		}

		BinaryWriter::~BinaryWriter() {
		}

		void BinaryWriter::write(uint8 value) {
			stream->write((unsigned char*)&value, sizeof(uint8));
		}

		void BinaryWriter::write(uint16 value) {
			stream->write((unsigned char*)&value, sizeof(uint16));
		}

		void BinaryWriter::write(uint32 value) {
			stream->write((unsigned char*)&value, sizeof(uint32));
		}

		void BinaryWriter::write(uint64 value) {
			stream->write((unsigned char*)&value, sizeof(uint64));
		}

		void BinaryWriter::write(int8 value) {
			stream->write((unsigned char*)&value, sizeof(int8));
		}

		void BinaryWriter::write(int16 value) {
			stream->write((unsigned char*)&value, sizeof(int16));
		}

		void BinaryWriter::write(int32 value) {
			stream->write((unsigned char*)&value, sizeof(int32));
		}

		void BinaryWriter::write(int64 value) {
			stream->write((unsigned char*)&value, sizeof(int64));
		}

		void BinaryWriter::write(float32 value) {
			stream->write((unsigned char*)&value, sizeof(float32));
		}

		void BinaryWriter::write(float64 value) {
			stream->write((unsigned char*)&value, sizeof(float64));
		}

		void BinaryWriter::write(const String& value) {
			write7BitEncodedInt(value.size());
			stream->write((unsigned char*)value.c_str(), sizeof(char) * value.size());
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

					if (index > 0) val |= 0x80;

					uint8 u8val = (uint8)val;

					stream->write((unsigned char*)&u8val, sizeof(uint8));
				}

				mask >>= 7;

				--index;
			}

			if (!reached && index < 0) {
				uint8 a = 0;

				stream->write(&a, sizeof(uint8));
			}
		}

		void BinaryWriter::flush() const {
			stream->flush();
		}
	}
}