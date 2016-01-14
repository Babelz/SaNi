#pragma once

#include "transform.hpp"
#include "trigonometric_func.hpp"
#include "geometric_func.hpp"

namespace sani {
	namespace math {
		template <typename T>
		Matrix4<T> translate(Matrix4<T> const& mat, Vector3<T> const& vec) {

			/*
				For programming purposes, OpenGL matrices are 16-value arrays with base vectors laid out contiguously in memory.
				The translation components occupy the 13th, 14th, and 15th elements of the 16-element matrix
			*/

			Matrix4<T> result;
			result[3] = mat[0] * vec[0] + mat[1] * vec[1] + mat[2] * vec[2] + mat[3];
			return result;
		}

		template <typename T>
		Matrix4<T> scale(Matrix4<T> const& mat, Vector3<T> const& vec) {
			Matrix4<T> result;

			result[0] = mat[0] * vec[0];
			result[1] = mat[1] * vec[1];
			result[2] = mat[2] * vec[2];
			result[3] = mat[3];

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
			result[1] = mat[0] * rot[1][0] + mat[1] * rot[1][1] + mat[2] * rot[1][2];
			result[2] = mat[0] * rot[2][0] + mat[1] * rot[2][1] + mat[2] * rot[2][2];
			result[3] = mat[3];
			return result;
		}

		template <typename T>
		Matrix4<T> ortho(const T left, const T right, const T bottom, const T top, const T zNear, const T zFar) {
			Matrix4<T> result;

			result[0][0] = static_cast<T>(2) / (right - left);
			result[1][1] = static_cast<T>(2) / (top - bottom);
			result[2][2] = -static_cast<T>(2) / (zFar - zNear);

			result[3][0] = -(right + left) / (right - left);
			result[3][1] = -(top + bottom) / (top - bottom);
			result[3][2] = -(zFar + zNear) / (zFar - zNear);

			return result;
		}

		template <typename T>
		Matrix4<T> perspective(const float fovy, const float ar, const float znear, const float zfar) {
			const T tanhf = math::tan(fovy / static_cast<T>(2));

			math::Mat4f perspective;

			perspective[0][0] = static_cast<T>(1) / (ar * tanhf);
			perspective[1][1] = static_cast<T>(1) / tanhf;
			perspective[2][2] = (zfar + znear) / (zfar - znear);
			perspective[2][3] = static_cast<T>(1);
			perspective[3][2] = -(static_cast<T>(2) * zfar * znear) / (zfar - znear);

			return perspective;
		}


		template <typename T>
		Matrix4<T> lookAt(const Vector3<T>& eye, const Vector3<T>& center, const Vector3<T>& up) {
			Vector3<T> const f(normalize(center - eye));
			Vector3<T> const s(normalize(cross(up, f)));
			Vector3<T> const u(cross(f, s));

			Matrix4<T> result;

			result[0][0] = s.x;
			result[1][0] = s.y;
			result[2][0] = s.z;
			result[0][1] = u.x;
			result[1][1] = u.y;
			result[2][1] = u.z;
			result[0][2] = f.x;
			result[1][2] = f.y;
			result[2][2] = f.z;
			result[3][0] = -dot(s, eye);
			result[3][1] = -dot(u, eye);
			result[3][2] = -dot(f, eye);

			return result;
		}
	}
}
