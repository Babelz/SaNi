#pragma once

#include "../matrix4.hpp"

namespace sani {
	namespace math {
		template <typename T>
		inline Matrix4<T>::Matrix4()
			: row1(T(1), T(0), T(0), T(0)),
			row2(T(0), T(1), T(0), T(0)),
			row3(T(0), T(0), T(1), T(0)),
			row4(T(0), T(0), T(0), T(1)) {

		}
		template <typename T>
		inline Matrix4<T>::Matrix4(const Vector4<T>& row1, const Vector4<T>& row2, const Vector4<T>& row3, const Vector4<T>& row4)
			: row1(row1), row2(row2), row3(row3), row4(row4) {

		}

		template <typename T>
		inline Matrix4<T>::Matrix4(const Matrix4<T>& mat)
			: row1(mat.row1.x, mat.row1.y, mat.row1.z, mat.row1.w),
			row2(mat.row2.x, mat.row2.y, mat.row2.z, mat.row2.w),
			row3(mat.row3.x, mat.row3.y, mat.row3.z, mat.row3.w),
			row4(mat.row4.x, mat.row4.y, mat.row4.z, mat.row4.w) {
		}

		template <typename T>
		inline Matrix4<T>::Matrix4(const T& m11, const T& m12, const T& m13, const T& m14,
			const T& m21, const T& m22, const T& m23, const T& m24,
			const T& m31, const T& m32, const T& m33, const T& m34,
			const T& m41, const T& m42, const T& m43, const T& m44)
			: row1(m11, m12, m13, m14),
			row2(m21, m22, m23, m24),
			row3(m31, m32, m33, m34),
			row4(m41, m42, m43, m44) {
		}

		template <typename T>
		template <typename U>
		inline Matrix4<T>::Matrix4(const Matrix4<U>& mat)
			: row1(mat[0]), row2(mat[1]), row3(mat[2]), row4(mat[3]) {
		}

		// comp

		template <typename T>
		inline bool Matrix4<T>::operator==(const Matrix4<T>& rhs) const {
			return row1.x == rhs.row1.x && row1.y == rhs.row1.y && row1.z == rhs.row1.z && row1.w == rhs.row1.w
				&& row2.x == rhs.row2.x && row2.y == rhs.row2.y && row2.z == rhs.row2.z && row2.w == rhs.row2.w
				&& row3.x == rhs.row3.x && row3.y == rhs.row3.y && row3.z == rhs.row3.z && row3.w == rhs.row3.w
				&& row4.x == rhs.row4.x && row4.y == rhs.row4.y && row4.z == rhs.row4.z && row4.w == rhs.row4.w;
		}

		template <typename T>
		inline bool Matrix4<T>::operator!=(const Matrix4<T>& rhs) const {
			return !(*this == rhs);
		}

		// assign

		template <typename T>
		inline const Matrix4<T>& Matrix4<T>::operator=(const Matrix4<T>& rhs) {
			if (this == &rhs) return *this;
			row1.x = rhs.row1.x;
			row1.y = rhs.row1.y;
			row1.z = rhs.row1.z;
			row1.w = rhs.row1.w;
			row2.x = rhs.row2.x;
			row2.y = rhs.row2.y;
			row2.z = rhs.row2.z;
			row2.w = rhs.row2.w;
			row3.x = rhs.row3.x;
			row3.y = rhs.row3.y;
			row3.z = rhs.row3.z;
			row3.w = rhs.row3.w;
			row4.x = rhs.row4.x;
			row4.y = rhs.row4.y;
			row4.z = rhs.row4.z;
			row4.w = rhs.row4.w;
			return *this;
		}


		template <typename T>
		inline Matrix4<T>& Matrix4<T>::operator+=(const Matrix4<T>& rhs) {
			row1 += rhs.row1;
			row2 += rhs.row2;
			row3 += rhs.row3;
			row4 += rhs.row4;
			return *this;
		}

		template <typename T>
		inline Matrix4<T>& Matrix4<T>::operator-=(const Matrix4<T>& rhs) {
			row1 -= rhs.row1;
			row2 -= rhs.row2;
			row3 -= rhs.row3;
			row4 -= rhs.row4;
			return *this;
		}

		template <typename T>
		inline Matrix4<T>& Matrix4<T>::operator*=(const Matrix4<T>& rhs) {
			return *this = *this * rhs;
		}

		template <typename T>
		inline Matrix4<T>& Matrix4<T>::operator*=(const T& rhs) {
			row1 *= rhs;
			row2 *= rhs;
			row3 *= rhs;
			row4 *= rhs;
			return *this;
		}

		template <typename T>
		inline Matrix4<T>& Matrix4<T>::operator/=(const T& rhs) {
			row1 /= rhs;
			row2 /= rhs;
			row3 /= rhs;
			row4 /= rhs;
			return *this;
		}

		// arith


		template <typename T>
		inline const Matrix4<T> Matrix4<T>::operator+(const Matrix4<T>& rhs) const {
			return Matrix4<T>(row1 + rhs.row1, row2 + rhs.row2, row3 + rhs.row3, row4 + rhs.row4);
		}

		template <typename T>
		inline const Matrix4<T> Matrix4<T>::operator-(const Matrix4<T>& rhs) const {
			return Matrix4<T>(row1 - rhs.row1, row2 - rhs.row2, row3 - rhs.row3, row4 - rhs.row4);
		}

		template <typename T>
		inline const Matrix4<T> Matrix4<T>::operator*(const Matrix4<T>& rhs) const {
			return Matrix4<T>(
				this->row1.x * rhs.row1.x + this->row1.y * rhs.row2.x + this->row1.z * rhs.row3.x + this->row1.w * rhs.row4.x,
				this->row1.x * rhs.row1.y + this->row1.y * rhs.row2.y + this->row1.z * rhs.row3.y + this->row1.w * rhs.row4.y,
				this->row1.x * rhs.row1.z + this->row1.y * rhs.row2.z + this->row1.z * rhs.row3.z + this->row1.w * rhs.row4.z,
				this->row1.x * rhs.row1.w + this->row1.y * rhs.row2.w + this->row1.z * rhs.row3.w + this->row1.w * rhs.row4.w,


				this->row2.x * rhs.row1.x + this->row2.y * rhs.row2.x + this->row2.z * rhs.row3.x + this->row2.w * rhs.row4.x,
				this->row2.x * rhs.row1.y + this->row2.y * rhs.row2.y + this->row2.z * rhs.row3.y + this->row2.w * rhs.row4.y,
				this->row2.x * rhs.row1.z + this->row2.y * rhs.row2.z + this->row2.z * rhs.row3.z + this->row2.w * rhs.row4.z,
				this->row2.x * rhs.row1.w + this->row2.y * rhs.row2.w + this->row2.z * rhs.row3.w + this->row2.w * rhs.row4.w,

				this->row3.x * rhs.row1.x + this->row3.y * rhs.row2.x + this->row3.z * rhs.row3.x + this->row3.w * rhs.row4.x,
				this->row3.x * rhs.row1.y + this->row3.y * rhs.row2.y + this->row3.z * rhs.row3.y + this->row3.w * rhs.row4.y,
				this->row3.x * rhs.row1.z + this->row3.y * rhs.row2.z + this->row3.z * rhs.row3.z + this->row3.w * rhs.row4.z,
				this->row3.x * rhs.row1.w + this->row3.y * rhs.row2.w + this->row3.z * rhs.row3.w + this->row3.w * rhs.row4.w, 

				this->row4.x * rhs.row1.x + this->row4.y * rhs.row2.x + this->row4.z * rhs.row3.x + this->row4.w * rhs.row4.x,
				this->row4.x * rhs.row1.y + this->row4.y * rhs.row2.y + this->row4.z * rhs.row3.y + this->row4.w * rhs.row4.y,
				this->row4.x * rhs.row1.z + this->row4.y * rhs.row2.z + this->row4.z * rhs.row3.z + this->row4.w * rhs.row4.z,
				this->row4.x * rhs.row1.w + this->row4.y * rhs.row2.w + this->row4.z * rhs.row3.w + this->row4.w * rhs.row4.w
				);
		}

		template <typename T>
		inline const Matrix4<T> Matrix4<T>::operator*(const T& rhs) const {
			return Matrix4<T>(row1 * rhs, row2 * rhs, row3 * rhs, row4 * rhs);
		}

		template <typename T>
		inline const Matrix4<T> Matrix4<T>::operator/(const T& rhs) const {
			return Matrix4<T>(row1 / rhs, row2 / rhs, row3 / rhs, row4 / rhs);
		}

		template <typename T>
		inline const Vector4<T> Matrix4<T>::operator*(const Vector4<T>& rhs) const {
			return Vector4<T>(
				this->row1.x * rhs.x + this->row1.y * rhs.y + this->row1.z * rhs.z + this->row1.w * rhs.w,
				this->row2.x * rhs.x + this->row2.y * rhs.y + this->row2.z * rhs.z + this->row2.w * rhs.w,
				this->row3.x * rhs.x + this->row3.y * rhs.y + this->row3.z * rhs.z + this->row3.w * rhs.w,
				this->row4.x * rhs.x + this->row4.y * rhs.y + this->row4.z * rhs.z + this->row4.w * rhs.w
				);
		}


		template<typename T>
		inline const Matrix4<T> operator*(const T& lhs, const Matrix4<T>& rhs) {
			return rhs * lhs;
		}


		template<typename T>
		inline const Vector4<T>& operator*=(Vector4<T>& lhs, const Matrix4<T>& rhs) {
			lhs = rhs * lhs;
			return lhs;
		}

		// index


		template <typename T>
		inline Vector4<T>& Matrix4<T>::operator[](const unsigned int i) {
			return const_cast<Vector4<T>&>(
				static_cast<const Matrix4<T>&>(*this)[i]);
		}


		template <typename T>
		inline const Vector4<T>& Matrix4<T>::operator[](const unsigned int i) const {
			SANI_ASSERT(i < Rows);
			return (&row1)[i];
		}
	}
}

