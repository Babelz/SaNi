#include "../matrix2.hpp"

namespace sani {
	namespace math {
		template <typename T>
		Matrix2<T>::Matrix2() 
			: row1(T(1), T(0)), row2(T(0),T(1)) {

		}
		template <typename T>
		Matrix2<T>::Matrix2(const Vector2<T>& row1, const Vector2<T>& row2) 
			: row1(row1), row2(row2) {

		}

		template <typename T>
		Matrix2<T>::Matrix2(const Matrix2<T>& mat) 
			: row1(mat.row1.x, mat.row1.y),
			  row2(mat.row2.x, mat.row2.y) {
		}

		template <typename T>
		Matrix2<T>::Matrix2(const T& m11, const T& m12, const T& m21, const T& m22) 
			: row1(m11, m12), 
			  row2(m21, m22) {

		}

		template <typename T>
		template <typename U>
		Matrix2<T>::Matrix2(const Matrix2<U>& mat) 
			: row1(static_cast<T>(mat.m11), static_cast<T>(mat.m12)),
			  row2(static_cast<T>(mat.m21), static_cast<T>(mat.m22)) {

		}

		// comp

		template <typename T>
		bool Matrix2<T>::operator==(const Matrix2<T>& rhs) const {
			return row1.x == rhs.row1.x && row1.y == rhs.row1.y
				&& row2.x == rhs.row2.x && row2.y == rhs.row2.y;
		}

		template <typename T>
		bool Matrix2<T>::operator!=(const Matrix2<T>& rhs) const {
			return !(*this == rhs);
		}

		// assign

		template <typename T>
		const Matrix2<T>& Matrix2<T>::operator=(const Matrix2<T>& rhs) {
			if (this == &rhs) return *this;
			row1.x = rhs.row1.x;
			row1.y = rhs.row1.y;
			row2.x = rhs.row2.x;
			row2.y = rhs.row2.y;
			return *this;
		}


		template <typename T>
		Matrix2<T>& Matrix2<T>::operator+=(const Matrix2<T>& rhs) {
			row1 += rhs.row1;
			row2 += rhs.row2;
			return *this;
		}

		template <typename T>
		Matrix2<T>& Matrix2<T>::operator-=(const Matrix2<T>& rhs) {
			row1 -= rhs.row1;
			row2 -= rhs.row2;
			return *this;
		}

		template <typename T>
		Matrix2<T>& Matrix2<T>::operator*=(const Matrix2<T>& rhs) {

		}

		template <typename T>
		Matrix2<T>& Matrix2<T>::operator*=(const T& rhs) {
			row1 *= rhs;
			row2 *= rhs;
			return *this;
		}

		template <typename T>
		Matrix2<T>& Matrix2<T>::operator/=(const T& rhs) {
			row1 /= rhs;
			row2 /= rhs;
			return *this;
		}

		// arith


		template <typename T>
		const Matrix2<T> Matrix2<T>::operator+(const Matrix2<T>& rhs) const {
			return Matrix2<T>(row1 + rhs.row1, row2 + rhs.row2);
		}

		template <typename T>
		const Matrix2<T> Matrix2<T>::operator-(const Matrix2<T>& rhs) const {
			return Matrix2<T>(row1 - rhs.row1, row2 - rhs.row2);
		}

		template <typename T>
		const Matrix2<T> Matrix2<T>::operator*(const Matrix2<T>& rhs) const {

		}

		template <typename T>
		const Matrix2<T> Matrix2<T>::operator*(const T& rhs) const {
			return Matrix2<T>(row1 * rhs, row2 * rhs);
		}

		template <typename T>
		const Matrix2<T> Matrix2<T>::operator/(const T& rhs) const {
			return Matrix2<T>(row1 / rhs, row2 / rhs);
		}

		template <typename T>
		const Vector2<T> Matrix2<T>::operator*(const Vector2<T>& rhs) const {

		}


		template<typename T>
		const Matrix2<T> operator*(const T& lhs, const Matrix2<T>& rhs) {
			return rhs * lhs;
		}


		template<typename T>
		const Vector2<T>& operator*=(Vector2<T>& lhs, const Matrix2<T>& rhs) {
			
		}

		// index


		template <typename T>
		Vector2<T>& Matrix2<T>::operator[](const unsigned int i) {
			return const_cast<Vector2<T>&>(
				static_cast<const Matrix2<T>&>(*this)[i]);
		}


		template <typename T>
		const Vector2<T>& Matrix2<T>::operator[](const unsigned int i) const {
			assert(i < Rows);
			return (&row1)[i];
		}

	}
}