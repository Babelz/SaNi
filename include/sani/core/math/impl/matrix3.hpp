#include "../matrix3.hpp"

namespace sani {
	namespace math {
		template <typename T>
		inline Matrix3<T>::Matrix3()
			:	row1(T(1), T(0), T(0)), 
				row2(T(0), T(1), T(0)), 
				row3(T(0), T(0), T(1)) {

		}
		template <typename T>
		inline Matrix3<T>::Matrix3(const Vector3<T>& row1, const Vector3<T>& row2, const Vector3<T>& row3)
			: row1(row1), row2(row2), row3(row3) {

		}

		template <typename T>
		inline Matrix3<T>::Matrix3(const Matrix3<T>& mat)
			:	row1(mat.row1.x, mat.row1.y, mat.row1.z),
				row2(mat.row2.x, mat.row2.y, mat.row2.z),
				row3(mat.row3.x, mat.row3.y, mat.row3.z) {
		}

		template <typename T>
		inline Matrix3<T>::Matrix3(const T& m11, const T& m12, const T& m13,
								   const T& m21, const T& m22, const T& m23,
									const T& m31, const T& m32, const T& m33)
			:	row1(m11, m12, m13),
				row2(m21, m22, m23),
				row3(m31, m32, m33) {
		}

		template <typename T>
		template <typename U>
		inline Matrix3<T>::Matrix3(const Matrix3<U>& mat)
			: row1(mat[0]), row2(mat[1]), row3(mat[2]) {
		}

		// comp

		template <typename T>
		inline bool Matrix3<T>::operator==(const Matrix3<T>& rhs) const {
			return row1.x == rhs.row1.x && row1.y == rhs.row1.y && row1.z == rhs.row1.z
				&& row2.x == rhs.row2.x && row2.y == rhs.row2.y && row2.z == rhs.row2.z
				&& row3.x == rhs.row3.x && row3.y == rhs.row3.y && row3.z == rhs.row3.z;
		}

		template <typename T>
		inline bool Matrix3<T>::operator!=(const Matrix3<T>& rhs) const {
			return !(*this == rhs);
		}

		// assign

		template <typename T>
		inline const Matrix3<T>& Matrix3<T>::operator=(const Matrix3<T>& rhs) {
			if (this == &rhs) return *this;
			row1.x = rhs.row1.x;
			row1.y = rhs.row1.y;
			row1.z = rhs.row1.z;
			row2.x = rhs.row2.x;
			row2.y = rhs.row2.y;
			row2.z = rhs.row2.z;
			row3.x = rhs.row3.x;
			row3.y = rhs.row3.y;
			row3.z = rhs.row3.z;
			return *this;
		}


		template <typename T>
		inline Matrix3<T>& Matrix3<T>::operator+=(const Matrix3<T>& rhs) {
			row1 += rhs.row1;
			row2 += rhs.row2;
			row3 += rhs.row3;
			return *this;
		}

		template <typename T>
		inline Matrix3<T>& Matrix3<T>::operator-=(const Matrix3<T>& rhs) {
			row1 -= rhs.row1;
			row2 -= rhs.row2;
			row3 -= rhs.row3;
			return *this;
		}

		template <typename T>
		inline Matrix3<T>& Matrix3<T>::operator*=(const Matrix3<T>& rhs) {
			return *this = *this * rhs;
		}

		template <typename T>
		inline Matrix3<T>& Matrix3<T>::operator*=(const T& rhs) {
			row1 *= rhs;
			row2 *= rhs;
			row3 *= rhs;
			return *this;
		}

		template <typename T>
		inline Matrix3<T>& Matrix3<T>::operator/=(const T& rhs) {
			row1 /= rhs;
			row2 /= rhs;
			row3 /= rhs;
			return *this;
		}

		// arith


		template <typename T>
		inline const Matrix3<T> Matrix3<T>::operator+(const Matrix3<T>& rhs) const {
			return Matrix3<T>(row1 + rhs.row1, row2 + rhs.row2, row3 + rhs.row3);
		}

		template <typename T>
		inline const Matrix3<T> Matrix3<T>::operator-(const Matrix3<T>& rhs) const {
			return Matrix3<T>(row1 - rhs.row1, row2 - rhs.row2, row3 - rhs.row3);
		}

		template <typename T>
		inline const Matrix3<T> Matrix3<T>::operator*(const Matrix3<T>& rhs) const {
			
			return Matrix3<T>(
				this->row1.x * rhs.row1.x + this->row1.y * rhs.row2.x + this->row1.z * rhs.row3.x,
				this->row1.x * rhs.row1.y + this->row1.y * rhs.row2.y + this->row1.z * rhs.row3.y,
				this->row1.x * rhs.row1.y + this->row1.y * rhs.row2.z + this->row1.z * rhs.row3.z,

				this->row2.x * rhs.row1.x + this->row2.y * rhs.row2.x + this->row2.z * rhs.row3.x,
				this->row2.x * rhs.row1.y + this->row2.y * rhs.row2.y + this->row2.z * rhs.row3.y,
				this->row2.x * rhs.row1.z + this->row2.y * rhs.row2.z + this->row2.z * rhs.row3.z,
				
				this->row3.x * rhs.row1.x + this->row3.y * rhs.row2.x + this->row3.z * rhs.row3.x,
				this->row3.x * rhs.row1.y + this->row3.y * rhs.row2.y + this->row3.z * rhs.row3.y,
				this->row3.x * rhs.row1.z + this->row3.y * rhs.row2.z + this->row3.z * rhs.row3.z
				);
		}

		template <typename T>
		inline const Matrix3<T> Matrix3<T>::operator*(const T& rhs) const {
			return Matrix3<T>(row1 * rhs, row2 * rhs, row3 * rhs);
		}

		template <typename T>
		inline const Matrix3<T> Matrix3<T>::operator/(const T& rhs) const {
			return Matrix3<T>(row1 / rhs, row2 / rhs, row3 / rhs);
		}

		template <typename T>
		inline const Vector3<T> Matrix3<T>::operator*(const Vector3<T>& rhs) const {
			return Vector3<T>(
				this->row1.x * rhs.x + this->row1.y * rhs.y + this->row1.z * rhs.z,
				this->row2.x * rhs.x + this->row2.y * rhs.y + this->row2.z * rhs.z,
				this->row3.x * rhs.x + this->row3.y * rhs.y + this->row3.z * rhs.z
				);
		}


		template<typename T>
		inline const Matrix3<T> operator*(const T& lhs, const Matrix3<T>& rhs) {
			return rhs * lhs;
		}


		template<typename T>
		inline const Vector3<T>& operator*=(Vector3<T>& lhs, const Matrix3<T>& rhs) {
			lhs = rhs * lhs;
			return lhs;
		}

		// index


		template <typename T>
		inline Vector3<T>& Matrix3<T>::operator[](const unsigned int i) {
			return const_cast<Vector3<T>&>(
				static_cast<const Matrix3<T>&>(*this)[i]);
		}


		template <typename T>
		inline const Vector3<T>& Matrix3<T>::operator[](const unsigned int i) const {
			assert(i < Rows);
			return (&row1)[i];
		}
	}
}