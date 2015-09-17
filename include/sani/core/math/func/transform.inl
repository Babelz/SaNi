#pragma once

#include "transform.hpp"
#include "trigonometric_func.hpp"

namespace sani {
	namespace math {
		template <typename T>
		Matrix4<T> translate(Matrix4<T> const& mat, Vector3<T> const& vec) {
			/*
			For programming purposes, OpenGL matrices are 16-value arrays with base vectors laid out contiguously in memory. 
			The translation components occupy the 13th, 14th, and 15th elements of the 16-element matrix
			TODO: DirectX has the same memory layout?
			*/
			Matrix4<T> result;
			result[3] = mat[0] * vec[0] + mat[1] * vec[1] + mat[2] * vec[2] + mat[3];
			return result;
		}

		template <typename T>
		Matrix4<T> rotate(Matrix4<T> const& mat, T angle, Vector3<T> const& axis) {
			T const a = angle;
			T const c = cos(a);
			T const s = sin(a);

			Vector3<T> tmp((T(1) - c)*axis);
			Matrix4<T> rot;
			rot[0][0] = c + tmp[0] * axis[0];
			rot[0][1] = tmp[0] * axis[1] + s * axis[2];
			rot[0][2] = tmp[0] * axis[2] - s * axis[1];

			rot[1][0] = tmp[1] * axis[0] - s * axis[2];
			rot[1][1] = c + tmp[1] * axis[1];
			rot[1][2] = tmp[1] * axis[2] + s * axis[0];

			rot[2][0] = tmp[2] * axis[0] + s * axis[1];
			rot[2][1] = tmp[2] * axis[1] - s * axis[0];
			rot[2][2] = c + tmp[2] * axis[2];

			Matrix4<T> result;
			result[0] = mat[0] * rot[0][0] + mat[1] * rot[0][1] + mat[2] * rot[0][2];
			result[0] = mat[0] * rot[1][0] + mat[1] * rot[1][1] + mat[2] * rot[1][2];
			result[0] = mat[0] * rot[2][0] + mat[1] * rot[2][1] + mat[2] * rot[2][2];
			result[3] = mat[3];
			return result;
		}
	}
}

