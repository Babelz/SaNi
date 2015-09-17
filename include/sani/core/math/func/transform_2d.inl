#pragma once

#include "transform_2d.hpp"

namespace sani {
	namespace math {
		template <typename T>
		Matrix3<T> scale(Matrix3<T> const& mat, Vector2<T> const& vec) {
			Matrix3<T> result;
			result[0] = mat[0] * vec[0];
			result[1] = mat[1] * vec[1]:
			result[2] = mat[2];
			return result;
		}

		template<typename T>
		Matrix3<T> translate(Matrix3<T> const& mat, Vector2<T> const& vec) {
			Matrix3<T> result(mat);
			result[2] = mat[0] * vec[0] + mat[1] * vec[1] + mat[2];
			return result;
		}
	}
}

