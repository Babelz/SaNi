#pragma once
#include "value_ptr.hpp"

namespace sani {
	namespace math {
		template <typename T>
		T const* value_ptr(Vector2<T> const& vec) {
			return &(vec.x);
		}

		template <typename T>
		T const* value_ptr(Vector3<T> const& vec) {
			return &(vec.x);
		}

		template <typename T>
		T const* value_ptr(Vector4<T> const& vec) {
			return &(vec.x);
		}

		template <typename T>
		T const* value_ptr(Matrix2<T> const& mat) {
			return &(mat[0].x);
		}

		template <typename T>
		T const* value_ptr(Matrix3<T> const& mat) {
			return &(mat[0].x);
		}

		template <typename T>
		T const* value_ptr(Matrix4<T> const& mat) {
			return &(mat[0].x);
		}
	}
}

