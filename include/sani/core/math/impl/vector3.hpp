#include "../vector3.hpp"

namespace sani {
	namespace math {
		template <typename T>
		template <typename U>
		inline Vector3<T>::Vector3(const Vector3<U>& vector)
			: x(static_cast<T>(vector.x)), 
			  y(static_cast<T>(vector.y)),
			  z(static_cast<T>(vector.z)){ }

		template <typename T>
		inline Vector3<T>::Vector3(const Vector3<T>& vector)
			: x(vector.x), y(vector.y), z(vector.z) { }

		template <typename T>
		inline Vector3<T>::Vector3(const T& x, const T& y, const T& z)
			: x(x), y(y), z(z) { }


		template <typename T>
		inline Vector3<T>::Vector3()
			: x(T()), y(T()), z(T()) { }

		template <typename T>
		inline Vector3<T>::Vector3(const T& value)x3
			: x(value), y(value), z(value) {

		}
		template <typename T>
		inline Vector3<T>::Vector3(const Vector2<T>& vector, const T& z)
			: x(vector.x), y(vector.y), z(z) {

		}

		template <typename T>
		inline Vector3<T>::~Vector3() { }

		// public funcs

		template <typename T>
		inline double Vector3<T>::lengthSquared() const {
			// lets calculate with higher precision
			double x = static_cast<double>(this->x);
			double y = static_cast<double>(this->y);
			double z = static_cast<double>(this->z);
			return x*x + y*y + z*z;
		}

		template <typename T>
		inline double Vector3<T>::length() const {
			return std::sqrt(lengthSquared());
		}

		template <typename T>
		inline bool Vector3<T>::isNormalized() const {
			return lengthSquared() == 1;
		}

		// operators
		template <typename T>
		inline bool Vector3<T>::operator==(const Vector3<T>& rhs) const {
			return x == rhs.x && y == rhs.y && z == rhs.z;
		}

		template <typename T>
		inline bool Vector3<T>::operator!=(const Vector3<T>& rhs) const {
			return !(*this == rhs);
		}

		template <typename T>
		inline bool Vector3<T>::operator<(const Vector3<T>& rhs) const {
			return lengthSquared() < rhs.lengthSquared();
		}

		template <typename T>
		inline bool Vector3<T>::operator<=(const Vector3<T>& rhs) const {
			return lengthSquared() <= rhs.lengthSquared();
		}

		template <typename T>
		inline bool Vector3<T>::operator>(const Vector3<T>& rhs) const {
			return lengthSquared() > rhs.lengthSquared();
		}

		template <typename T>
		inline bool Vector3<T>::operator>=(const Vector3<T>& rhs) const {
			return lengthSquared() > rhs.lengthSquared();
		}

		// Arithmetics
		template <typename T>
		inline const Vector3<T> Vector3<T>::operator-() const {
			return Vector3<T>(-x, -y, -z);
		}

		template <typename T>
		inline const Vector3<T> Vector3<T>::operator*(const Vector3<T>& rhs) const {
			return Vector3<T>(x * rhs.x, y * rhs.y, z * rhs.z);
		}

		template <typename T>
		inline const Vector3<T> Vector3<T>::operator*(const T& rhs) const {
			return Vector3<T>(x * rhs, y * rhs, z * rhs);
		}

		template <typename T>
		inline const Vector3<T> Vector3<T>::operator+(const Vector3<T>& rhs) const {
			return Vector3<T>(x + rhs.x, y + rhs.y, z + rhs.z);
		}

		template <typename T>
		inline const Vector3<T> Vector3<T>::operator-(const Vector3<T>& rhs) const {
			return *this + -rhs;
		}

		template <typename T>
		inline const Vector3<T> Vector3<T>::operator/(const Vector3<T>& rhs) const {
			return Vector3<T>(x / rhs.x, y / rhs.y, z / rhs.z);
		}

		template <typename T>
		inline const Vector3<T> Vector3<T>::operator/(const T& rhs) const {
			return Vector3<T>(x / rhs, y / rhs, z / rhs);
		}

		template <typename T>
		inline const Vector3<T> operator*(const T& lhs, const Vector3<T>& rhs) {
			return Vector3<T>(lhs * rhs.x, lhs * rhs.y, lhs * rhs.z);
		}

		// Assignments
		template <typename T>
		inline const Vector3<T>& Vector3<T>::operator=(const Vector3<T>& rhs) {
			if (this == &rhs) return *this;

			x = rhs.x;
			y = rhs.y;
			z = rhs.z;
			return *this;
		}

		template <typename T>
		inline Vector3<T>& Vector3<T>::operator+=(const Vector3& rhs) {
			x += rhs.x;
			y += rhs.y;
			z += rhs.z;
			return *this;
		}

		template <typename T>
		inline Vector3<T>& Vector3<T>::operator-=(const Vector3<T>& rhs) {
			x -= rhs.x;
			y -= rhs.y;
			z -= rhs.z;
			return *this;
		}

		template <typename T>
		inline Vector3<T>& Vector3<T>::operator*=(const Vector3<T>& rhs) {
			x *= rhs.x;
			y *= rhs.y;
			z *= rhs.z;
			return *this;
		}

		template <typename T>
		inline Vector3<T>& Vector3<T>::operator/=(const Vector3<T>& rhs) {
			x /= rhs.x;
			y /= rhs.y;
			z /= rhs.z;
			return *this;
		}

		template <typename T>
		inline Vector3<T>& Vector3<T>::operator*=(const T& rhs) {
			x *= rhs;
			y *= rhs;
			z *= rhs;
			return *this;
		}

		template <typename T>
		inline Vector3<T>& Vector3<T>::operator/=(const T& rhs) {
			x /= rhs;
			y /= rhs;
			z /= rhs;
			return *this;
		}

		// Indexer
		template <typename T>
		inline const T& Vector3<T>::operator[](unsigned int i) const {
			SANI_ASSERT(i < Components);
			return (&x)[i];
		}

		template <typename T>
		inline T& Vector3<T>::operator[](unsigned int i) {
			return const_cast<T&>(
				static_cast<const Vector3<T>&>(*this)[i]);
		}
	}
}