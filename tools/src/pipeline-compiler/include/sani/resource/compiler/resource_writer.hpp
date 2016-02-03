#pragma once
#include "sani/platform/platform_config.hpp"

#if SANI_TARGET_PLATFORM == SANI_PLATFORM_WIN32

#include "sani/platform/file/binary_writer.hpp"
#include "sani/core/math/math.hpp"
#include <vector>
#include <typeindex>
#include <unordered_map>
#include "sani/core/io/memory_stream.hpp"

SANI_FORWARD_DECLARE_2(sani, io, FileStream);
SANI_FORWARD_DECLARE_3(sani, resource, compiler, ResourceTypeWriter);
SANI_FORWARD_DECLARE_3(sani, resource, compiler, ResourceCompiler);
SANI_FORWARD_DECLARE_2(sani, resource, ResourceItem);

namespace sani {

	using namespace math;
	using namespace io;

	namespace resource {

		namespace compiler {

			class ResourceWriter : public io::BinaryWriter {
			private:
				static const char Platforms[];
				static const uint8 Version = 1;

				std::unordered_map<std::type_index, ResourceTypeWriter*> writers;
				const ResourceCompiler* compiler;

				ResourceTypeWriter* getWriter(const std::type_index&);

				/// Writes the header which consists of
				/// first 3 magic bytes S, N, B, then platform name
				/// and Version number
				void writeHeader();

				/// Writers the typewriters used to write this object
				void writeTypeWriters();

				MemoryStream memoryStream;
				FileStream* fileStream;
			public:
				// This assumes the file is opened already!
				ResourceWriter(FileStream* fileStream, const ResourceCompiler* compiler);

				~ResourceWriter();

				/// Writes and flushes the object to stream
				/// @see ResourceWriter::writeHeader
				/// @see ResourceWriter::writeTypeWriters
				/// @see ResourceWriter::writeObject
				void flush(const std::type_index&, const ResourceItem*);

				void writeObject(const std::type_index&, const ResourceItem*);

				void writeMatrix(const math::Matrix4<float32>& mat);

				void writeRectangle(const math::Rectangle<int32>& rect);
			};
		}
	}
}

#include "sani/resource/compiler/impl/resource_writer.hpp"

#endif