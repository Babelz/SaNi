#pragma once	

#include "sani/platform/platform_config.hpp"

#if SANI_TARGET_PLATFORM == SANI_PLATFORM_WIN32

#include "resource_writer.hpp"
#include "sani/resource/compiler/resource_compiler.hpp"

namespace sani {

	namespace resource {

		namespace compiler {

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

#endif