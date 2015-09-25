#pragma once

#include "sani/resource/resource_type_reader.hpp"

namespace sani {
	namespace resource {
		class Uint8Reader : public ResourceTypeReader {
		public:
			String getReaderName() const { return "sani::resource::Uint8Reader"; }
			/// Reads Uint8
			void read(ResourceReader* reader);
		};

		class Uint16Reader : public ResourceTypeReader {
		public:
			String getReaderName() const { return "sani::resource::Uint16Reader"; }
			/// Reads Uint16
			void read(ResourceReader* reader);
		};

		class Uint32Reader : public ResourceTypeReader {
		public:
			String getReaderName() const { return "sani::resource::Uint32Reader"; }
			/// Reads Uint32
			void read(ResourceReader* reader);
		};

		class Uint64Reader : public ResourceTypeReader {
		public:
			String getReaderName() const { return "sani::resource::Uint64Reader"; }
			/// Reads Uint64
			void read(ResourceReader* reader);
		};

		class Int8Reader : public ResourceTypeReader {
		public:
			String getReaderName() const { return "sani::resource::Int8Reader"; }
			/// Reads Int8
			void read(ResourceReader* reader);
		};

		class Int16Reader : public ResourceTypeReader {
		public:
			String getReaderName() const { return "sani::resource::Int16Reader"; }
			/// Reads Int16
			void read(ResourceReader* reader);
		};

		class Int32Reader : public ResourceTypeReader {
		public:
			String getReaderName() const { return "sani::resource::Int32Reader"; }
			/// Reads Int32
			void read(ResourceReader* reader);
		};

		class Int64Reader : public ResourceTypeReader {
		public:
			String getReaderName() const { return "sani::resource::Int64Reader"; }
			/// Reads Int64
			void read(ResourceReader* reader);
		};

		class SingleReader : public ResourceTypeReader {
		public:
			String getReaderName() const { return "sani::resource::SingleReader"; }
			/// Reads float32
			void read(ResourceReader* reader);
		};

		class DoubleReader : public ResourceTypeReader {
		public:
			String getReaderName() const { return "sani::resource::DoubleReader"; }
			/// Reads float64
			void read(ResourceReader* reader);
		};

		class CharReader : public ResourceTypeReader {
		public:
			String getReaderName() const { return "sani::resource::CharReader"; }
			/// Reads char
			void read(ResourceReader* reader);
		};

		class StringReader : public ResourceTypeReader {
		public:
			String getReaderName() const { return "sani::resource::StringReader"; }
			/// Reads string
			void read(ResourceReader* reader);
		};

		class ByteReader : public ResourceTypeReader {
		public:
			String getReaderName() const { return "sani::resource::ByteReader"; }
			/// Reads byte
			void read(ResourceReader* reader);
		};
	}
}