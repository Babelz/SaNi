#pragma once

#include "sani/forward_declare.hpp"
#include "sani/precompiled.hpp"
#include <cstdio>

namespace sani {
	namespace io {
		class BinaryWriter {
		private:
			FILE* file;
		public:
			BinaryWriter();
			BinaryWriter(FILE* file);
			~BinaryWriter();

			void write(uint16 value);
			void write(uint32 value);
			void write(uint64 value);
			void write(int16 value);
			void write(int32 value);
			void write(int64 value);
			void write(float32 value);
			void write(float64 value);
			void write(const String& value);
			void write7BitEncodedInt(uint64 value);
		};
	}
}