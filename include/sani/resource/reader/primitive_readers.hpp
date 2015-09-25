#pragma once

#include "sani/resource/reader/resource_type_reader.hpp"

namespace sani {
	namespace resource {
		namespace reader {
			class Uint8Reader : public ResourceTypeReader {
			public:
				String getReaderName() const { return "sani::resource::reader::Uint8Reader"; }
				/// Reads Uint8
				void read(ResourceReader* reader);
			};

			class Uint16Reader : public ResourceTypeReader {
			public:
				String getReaderName() const { return "sani::resource::reader::Uint16Reader"; }
				/// Reads Uint16
				void read(ResourceReader* reader);
			};

			class Uint32Reader : public ResourceTypeReader {
			public:
				String getReaderName() const { return "sani::resource::reader::Uint32Reader"; }
				/// Reads Uint32
				void read(ResourceReader* reader);
			};

			class Uint64Reader : public ResourceTypeReader {
			public:
				String getReaderName() const { return "sani::resource::reader::Uint64Reader"; }
				/// Reads Uint64
				void read(ResourceReader* reader);
			};

			class Int8Reader : public ResourceTypeReader {
			public:
				String getReaderName() const { return "sani::resource::reader::Int8Reader"; }
				/// Reads Int8
				void read(ResourceReader* reader);
			};

			class Int16Reader : public ResourceTypeReader {
			public:
				String getReaderName() const { return "sani::resource::reader::Int16Reader"; }
				/// Reads Int16
				void read(ResourceReader* reader);
			};

			class Int32Reader : public ResourceTypeReader {
			public:
				String getReaderName() const { return "sani::resource::reader::Int32Reader"; }
				/// Reads Int32
				void read(ResourceReader* reader);
			};

			class Int64Reader : public ResourceTypeReader {
			public:
				String getReaderName() const { return "sani::resource::reader::Int64Reader"; }
				/// Reads Int64
				void read(ResourceReader* reader);
			};

			class SingleReader : public ResourceTypeReader {
			public:
				String getReaderName() const { return "sani::resource::reader::SingleReader"; }
				/// Reads float32
				void read(ResourceReader* reader);
			};

			class DoubleReader : public ResourceTypeReader {
			public:
				String getReaderName() const { return "sani::resource::reader::DoubleReader"; }
				/// Reads float64
				void read(ResourceReader* reader);
			};

			class CharReader : public ResourceTypeReader {
			public:
				String getReaderName() const { return "sani::resource::reader::CharReader"; }
				/// Reads char
				void read(ResourceReader* reader);
			};

			class StringReader : public ResourceTypeReader {
			public:
				String getReaderName() const { return "sani::resource::reader::StringReader"; }
				/// Reads string
				void read(ResourceReader* reader);
			};

			class ByteReader : public ResourceTypeReader {
			public:
				String getReaderName() const { return "sani::resource::reader::ByteReader"; }
				/// Reads byte
				void read(ResourceReader* reader);
			};
		}
	}
}