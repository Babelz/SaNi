#pragma once	
#include "resource_writer.hpp"
namespace sani {
	namespace resource {
		namespace compiler {

			template <class T>
			ResourceTypeWriter* ResourceWriter::getWriter() {
				std::type_index info = std::type_index(typeid(T));
				// we dont have writer yet lets add it
				if (writers.find(info) == writers.end()) {
					ResourceTypeWriter* w = compiler->getWriter<T>();
					writers[std::type_index(typeid(T))] = w;
					return w;
				}
				// we have the typewriter already
				return writers[std::type_index(typeid(T))];
			}

			template <class T>
			void ResourceWriter::writeObject(const T* obj) {
				if (obj == nullptr) {
					throw std::runtime_error("obj is nullptr");
				}
				ResourceTypeWriter* writer = getWriter<T>();
				if (writer == nullptr) {
					throw std::runtime_error("Cant get writer for T");
				}
				writer->write(this, obj);
			}

			template <class T>
			void ResourceWriter::flush(const T* obj) {
				// this is hax, just so we have the writer in list...
				getWriter<T>();
				// write the header..
				writeHeader();
				// write the readers to deserialize
				writeTypeWriters();
				// write the final object..
				writeObject(obj);

				BinaryWriter::flush();
			}

			template <class T>
			void ResourceWriter::writeContainer(const std::vector<T>& v) {
				for (size_t i = 0; i < v.size(); ++i) {
					write(v[i]);
				}
			}

			template <class T>
			void ResourceWriter::writeMatrix(const math::Matrix2<T>& mat) {
				for (size_t i = 0; i < 2; ++i)
					write(mat[i]);
			}

			template <class T>
			void ResourceWriter::writeMatrix(const math::Matrix3<T>& mat) {
				for (size_t i = 0; i < 3; ++i)
					write(mat[i]);
			}

			template <class T>
			void ResourceWriter::writeMatrix(const math::Matrix4<T>& mat) {
				for (size_t i = 0; i < 4; ++i)
					write(mat[i]);
			}

			template <class T>
			void ResourceWriter::writeVector(const math::Vector2<T>& vec) {
				for (size_t i = 0; i < 2; ++i)
					write(vec[i]);
			}

			template <class T>
			void ResourceWriter::writeVector(const math::Vector3<T>& vec) {
				for (size_t i = 0; i < 3; ++i)
					write(vec[i]);
			}

			template <class T>
			void ResourceWriter::writeVector(const math::Vector4<T>& vec) {
				for (size_t i = 0; i < 4; ++i)
					write(vec[i]);
			}
		}
	}
}