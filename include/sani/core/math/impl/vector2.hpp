#include "../vector2.hpp"
#include <cassert>
namespace sani {
	namespace math {
		template <typename T> 
		template <typename U>
		Vector2<T>::Vector2(const Vector2<U>& vector)
			: x(static_cast<T>(vector.x)), y(static_cast<T>(vector.y)) { }

		template <typename T>
		Vector2<T>::Vector2(const Vector2<T>& vector)
			: x(vector.x), y(vector.y) { }

		template <typename T>
		Vector2<T>::Vector2(const T& x, const T& y) : x(x), y(y) { }


		template <typename T>
		Vector2<T>::Vector2()
			: x(T()), y(T()) { }

		template <typename T>
		Vector2<T>::Vector2(const T& value) : x(value), y(value) {

		}

		template <typename T>
		Vector2<T>::~Vector2() { }

		// public funcs

		template <typename T>
		double Vector2<T>::lengthSquared() const {
			// lets calculate with higher precision
			double x = static_cast<double>(this->x);
			double y = static_cast<double>(this->y);
			return x*x + y*y;
		}

		template <typename T>
		double Vector2<T>::length() const {
			return std::sqrt(lengthSquared());
		}

		template <typename T>
		bool Vector2<T>::isNormalized() const {
			return lengthSquared() == 1;
		}

		// operators
		template <typename T>
		bool Vector2<T>::operator==(const Vector2<T>& rhs) const {
			return x == rhs.x && y == rhs.y;
		}

		template <typename T>
		bool Vector2<T>::operator!=(const Vector2<T>& rhs) const {
			return !(*this == rhs);
		}

		template <typename T>
		bool Vector2<T>::operator<(const Vector2<T>& rhs) const {
			return lengthSquared() < rhs.lengthSquared();
		}

		template <typename T>
		bool Vector2<T>::operator<=(const Vector2<T>& rhs) const {
			return lengthSquared() <= rhs.lengthSquared();
		}

		template <typename T>
		bool Vector2<T>::operator>(const Vector2<T>& rhs) const {
			return lengthSquared() > rhs.lengthSquared();
		}

		template <typename T>
		bool Vector2<T>::operator>=(const Vector2<T>& rhs) const {
			return lengthSquared() > rhs.lengthSquared();
		}

		// Arithmetics
		template <typename T>
		const Vector2<T> Vector2<T>::operator-() const {
			return Vector2<T>(-x, -y);
		}

		template <typename T>
		const Vector2<T> Vector2<T>::operator*(const Vector2<T>& rhs) const {
			return Vector2<T>(x * rhs.x, y * rhs.y);
		}

		template <typename T>
		const Vector2<T> Vector2<T>::operator*(const T& rhs) const {
			return Vector2<T>(x * rhs, y * rhs);
		}

		template <typename T>
		const Vector2<T> Vector2<T>::operator+(const Vector2<T>& rhs) const {
			return Vector2<T>(x + rhs.x, y + rhs.y);
		}

		template <typename T>
		const Vector2<T> Vector2<T>::operator-(const Vector2<T>& rhs) const {
			return *this + -rhs;
		}

		template <typename T>
		const Vector2<T> Vector2<T>::operator/(const Vector2<T>& rhs) const {
			return Vector2<T>(x / rhs.x, y / rhs.y);
		}

		template <typename T>
		const Vector2<T> Vector2<T>::operator/(const T& rhs) const {
			return Vector2<T>(x / rhs, y / rhs);
		}

		template <typename T>
		const Vector2<T> operator*(const T& lhs, const Vector2<T>& rhs) {
			return Vector2<T>(lhs * rhs.x, lhs * rhs.y);
		}

		// Assignments
		template <typename T>
		const Vector2<T>& Vector2<T>::operator=(const Vector2<T>& rhs) {
			if (this == &rhs) return *this;

			x = rhs.x;
			y = rhs.y;
			return *this;
		}

		template <typename T>
		Vector2<T>& Vector2<T>::operator+=(const Vector2& rhs) {
			x += rhs.x;
			y += rhs.y;
			return *this;
		}

		template <typename T>
		Vector2<T>& Vector2<T>::operator-=(const Vector2<T>& rhs) {
			x -= rhs.x;
			y -= rhs.y;
			return *this;
		}

		template <typename T>
		Vector2<T>& Vector2<T>::operator*=(const Vector2<T>& rhs) {
			x *= rhs.x;
			y *= rhs.y;
			return *this;
		}

		template <typename T>
		Vector2<T>& Vector2<T>::operator/=(const Vector2<T>& rhs) {
			x /= rhs.x;
			y /= rhs.y;
			return *this;
		}

		template <typename T>
		Vector2<T>& Vector2<T>::operator*=(const T& rhs) {
			x *= rhs;
			y *= rhs;
			return *this;
		}

		template <typename T>
		Vector2<T>& Vector2<T>::operator/=(const T& rhs) {
			x /= rhs;
			y /= rhs;
			return *this;
		}

		// Indexer
		template <typename T>
		const T& Vector2<T>::operator[](unsigned int i) const {
			assert(i < Components);
			return (&x)[i];
		}

		template <typename T>
		T& Vector2<T>::operator[](unsigned int i) {
			return const_cast<T&>(
				static_cast<const Vector2<T>&>(*this)[i]);
		}
	}
}



