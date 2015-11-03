#pragma once
#include "sani/platform/file/binary_writer.hpp"
#include "sani/core/math/math.hpp"
#include <vector>
#include <typeindex>
#include <map>
SANI_FORWARD_DECLARE_2(sani, io, FileStream);
SANI_FORWARD_DECLARE_3(sani, resource, compiler, ResourceTypeWriter);
namespace sani {
	using namespace math;
	using namespace io;
	namespace resource {
		namespace compiler {
			class ResourceWriter : public io::BinaryWriter {
			private:
				static const char Platforms[];
				static const uint8 Version = 1;
				std::map<std::type_index, ResourceTypeWriter*> writers;
			public:

				// This assumes the file is opened already!
				ResourceWriter(const FileStream* stream);
				~ResourceWriter();

				/// Writes the header which consists of
				/// first 3 magic bytes S, N, B, then platform name
				/// and Version number
				void writeHeader();

				template <class T>
				ResourceTypeWriter* getWriter();

				template <class T>
				void writeObject(const T* obj);

				template <class T>
				void writeContainer(const std::vector<T>& v);

				template <class T>
				void writeMatrix(const math::Matrix2<T>& mat);

				template <class T>
				void writeMatrix(const math::Matrix3<T>& mat);

				template <class T>
				void writeMatrix(const math::Matrix4<T>& mat);

				template <class T>
				void writeVector(const math::Vector2<T>& vec);

				template <class T>
				void writeVector(const math::Vector3<T>& vec);

				template <class T>
				void writeVector(const math::Vector4<T>& vec);
			};
		}
	}
}
#include "resource_writer.inl"