#include "sani/debug.hpp"
#include "../matrix2.hpp"

/*

	TODO: should these be moved to .inl files?

*/

namespace sani {
	namespace math {
		template <typename T>
		inline Matrix2<T>::Matrix2()
			: row1(T(1), T(0)), row2(T(0),T(1)) {

		}
		template <typename T>
		inline Matrix2<T>::Matrix2(const Vector2<T>& row1, const Vector2<T>& row2)
			: row1(row1), row2(row2) {

		}

		template <typename T>
		inline Matrix2<T>::Matrix2(const Matrix2<T>& mat)
			: row1(mat.row1.x, mat.row1.y),
			  row2(mat.row2.x, mat.row2.y) {
		}

		template <typename T>
		inline Matrix2<T>::Matrix2(const T& m11, const T& m12, const T& m21, const T& m22)
			: row1(m11, m12), 
			  row2(m21, m22) {

		}

		template <typename T>
		template <typename U>
		inline Matrix2<T>::Matrix2(const Matrix2<U>& mat)
			: row1(mat[0]), row2(mat[1]) {

		}

		// comp

		template <typename T>
		inline bool Matrix2<T>::operator==(const Matrix2<T>& rhs) const {
			return row1.x == rhs.row1.x && row1.y == rhs.row1.y
				&& row2.x == rhs.row2.x && row2.y == rhs.row2.y;
		}

		template <typename T>
		inline bool Matrix2<T>::operator!=(const Matrix2<T>& rhs) const {
			return !(*this == rhs);
		}

		// assign

		template <typename T>
		inline const Matrix2<T>& Matrix2<T>::operator=(const Matrix2<T>& rhs) {
			if (this == &rhs) return *this;
			row1.x = rhs.row1.x;
			row1.y = rhs.row1.y;
			row2.x = rhs.row2.x;
			row2.y = rhs.row2.y;
			return *this;
		}


		template <typename T>
		inline Matrix2<T>& Matrix2<T>::operator+=(const Matrix2<T>& rhs) {
			row1 += rhs.row1;
			row2 += rhs.row2;
			return *this;
		}

		template <typename T>
		inline Matrix2<T>& Matrix2<T>::operator-=(const Matrix2<T>& rhs) {
			row1 -= rhs.row1;
			row2 -= rhs.row2;
			return *this;
		}

		template <typename T>
		inline Matrix2<T>& Matrix2<T>::operator*=(const Matrix2<T>& rhs) {
			return *this = *this * rhs;
		}

		template <typename T>
		inline Matrix2<T>& Matrix2<T>::operator*=(const T& rhs) {
			row1 *= rhs;
			row2 *= rhs;
			return *this;
		}

		template <typename T>
		inline Matrix2<T>& Matrix2<T>::operator/=(const T& rhs) {
			row1 /= rhs;
			row2 /= rhs;
			return *this;
		}

		// arith


		template <typename T>
		inline const Matrix2<T> Matrix2<T>::operator+(const Matrix2<T>& rhs) const {
			return Matrix2<T>(row1 + rhs.row1, row2 + rhs.row2);
		}

		template <typename T>
		inline const Matrix2<T> Matrix2<T>::operator-(const Matrix2<T>& rhs) const {
			return Matrix2<T>(row1 - rhs.row1, row2 - rhs.row2);
		}

		template <typename T>
		inline const Matrix2<T> Matrix2<T>::operator*(const Matrix2<T>& rhs) const {
			return Matrix2<T>(
				this->row1.x * rhs.row1.x + this->row1.y * rhs.row2.x,
				this->row1.x * rhs.row1.y + this->row1.y * rhs.row2.y,
				this->row2.x * rhs.row1.x + this->row2.y * rhs.row2.x,
				this->row2.x * rhs.row1.y + this->row2.y * rhs.row2.y);
		}

		template <typename T>
		inline const Matrix2<T> Matrix2<T>::operator*(const T& rhs) const {
			return Matrix2<T>(row1 * rhs, row2 * rhs);
		}

		template <typename T>
		inline const Matrix2<T> Matrix2<T>::operator/(const T& rhs) const {
			return Matrix2<T>(row1 / rhs, row2 / rhs);
		}

		template <typename T>
		inline const Vector2<T> Matrix2<T>::operator*(const Vector2<T>& rhs) const {
			return Vector2<T>(
				this->row1.x * rhs.x + this->row1.y * rhs.y,
				this->row2.x * rhs.x + this->row2.y * rhs.y
				);
		}


		template<typename T>
		inline const Matrix2<T> operator*(const T& lhs, const Matrix2<T>& rhs) {
			return rhs * lhs;
		}


		template<typename T>
		inline const Vector2<T>& operator*=(Vector2<T>& lhs, const Matrix2<T>& rhs) {
			lhs = rhs * lhs;
			return lhs;
		}

		// index


		template <typename T>
		inline Vector2<T>& Matrix2<T>::operator[](const unsigned int i) {
			return const_cast<Vector2<T>&>(
				static_cast<const Matrix2<T>&>(*this)[i]);
		}


		template <typename T>
		inline const Vector2<T>& Matrix2<T>::operator[](const unsigned int i) const {
			SANI_ASSERT(i < Rows);
			return (&row1)[i];
		}

	}
}