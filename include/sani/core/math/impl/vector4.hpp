#include "../vector4.hpp"

namespace sani {
	namespace math {
		template <typename T>
		template <typename U>
		inline Vector4<T>::Vector4(const Vector4<U>& vector)
			: x(static_cast<T>(vector.x)),
			y(static_cast<T>(vector.y)),
			z(static_cast<T>(vector.z)), 
			w(static_cast<T>(vector.w)){ }

		template <typename T>
		inline Vector4<T>::Vector4(const Vector4<T>& vector)
			: x(vector.x), y(vector.y), z(vector.z), w(vector.w) { }

		template <typename T>
		inline Vector4<T>::Vector4(const T& x, const T& y, const T& z, const T& w)
			: x(x), y(y), z(z), w(w) { }


		template <typename T>
		inline Vector4<T>::Vector4()
			: x(T()), y(T()), z(T()), w(T()) { }

		template <typename T>
		inline Vector4<T>::Vector4(const T& value)
			: x(value), y(value), z(value), w(value) {

		}

		template <typename T>
		inline Vector4<T>::Vector4(const Vector2<T>& vector, const T& z, const T& w)
			: x(vector.x), y(vector.y), z(z), w(w) {

		}
		template <typename T>
		inline Vector4<T>::Vector4(const Vector2<T>& vec1, const Vector2<T>& vec2)
			: x(vec1.x), y(vec1.y), z(vec2.x), w(vec2.y) {

		}

		template <typename T>
		inline Vector4<T>::Vector4(const Vector3<T>& vector, const T& w)
			: x(vector.x), y(vector.y), z(vector.z), w(w) {

		}

		template <typename T>
		inline Vector4<T>::~Vector4() { }

		// public funcs

		template <typename T>
		inline double Vector4<T>::lengthSquared() const {
			// lets calculate with higher precision
			double x = static_cast<double>(this->x);
			double y = static_cast<double>(this->y);
			double z = static_cast<double>(this->z);
			double w = static_cast<double>(this->w);
			return x*x + y*y + z*z + w*w;
		}

		template <typename T>
		inline double Vector4<T>::length() const {
			return std::sqrt(lengthSquared());
		}

		template <typename T>
		inline bool Vector4<T>::isNormalized() const {
			return lengthSquared() == 1;
		}

		// operators
		template <typename T>
		inline bool Vector4<T>::operator==(const Vector4<T>& rhs) const {
			return x == rhs.x && y == rhs.y && z == rhs.z && w == rhs.w;
		}

		template <typename T>
		inline bool Vector4<T>::operator!=(const Vector4<T>& rhs) const {
			return !(*this == rhs);
		}

		template <typename T>
		inline bool Vector4<T>::operator<(const Vector4<T>& rhs) const {
			return lengthSquared() < rhs.lengthSquared();
		}

		template <typename T>
		inline bool Vector4<T>::operator<=(const Vector4<T>& rhs) const {
			return lengthSquared() <= rhs.lengthSquared();
		}

		template <typename T>
		inline bool Vector4<T>::operator>(const Vector4<T>& rhs) const {
			return lengthSquared() > rhs.lengthSquared();
		}

		template <typename T>
		inline bool Vector4<T>::operator>=(const Vector4<T>& rhs) const {
			return lengthSquared() > rhs.lengthSquared();
		}

		// Arithmetics
		template <typename T>
		inline const Vector4<T> Vector4<T>::operator-() const {
			return Vector4<T>(-x, -y, -z, -w);
		}

		template <typename T>
		inline const Vector4<T> Vector4<T>::operator*(const Vector4<T>& rhs) const {
			return Vector4<T>(x * rhs.x, y * rhs.y, z * rhs.z, w * rhs.w);
		}

		template <typename T>
		inline const Vector4<T> Vector4<T>::operator*(const T& rhs) const {
			return Vector4<T>(x * rhs, y * rhs, z * rhs, w * rhs);
		}

		template <typename T>
		inline const Vector4<T> Vector4<T>::operator+(const Vector4<T>& rhs) const {
			return Vector4<T>(x + rhs.x, y + rhs.y, z + rhs.z, w + rhs.w);
		}

		template <typename T>
		inline const Vector4<T> Vector4<T>::operator-(const Vector4<T>& rhs) const {
			return *this + -rhs;
		}

		template <typename T>
		inline const Vector4<T> Vector4<T>::operator/(const Vector4<T>& rhs) const {
			return Vector4<T>(x / rhs.x, y / rhs.y, z / rhs.z, w / rhs.w);
		}

		template <typename T>
		inline const Vector4<T> Vector4<T>::operator/(const T& rhs) const {
			return Vector4<T>(x / rhs, y / rhs, z / rhs, w / rhs);
		}

		template <typename T>
		inline const Vector4<T> operator*(const T& lhs, const Vector4<T>& rhs) {
			return Vector4<T>(lhs * rhs.x, lhs * rhs.y, lhs * rhs.z, lhs * rhs.w);
		}

		// Assignments
		template <typename T>
		inline const Vector4<T>& Vector4<T>::operator=(const Vector4<T>& rhs) {
			if (this == &rhs) return *this;

			x = rhs.x;
			y = rhs.y;
			z = rhs.z;
			w = rhs.w;
			return *this;
		}

		template <typename T>
		inline Vector4<T>& Vector4<T>::operator+=(const Vector4& rhs) {
			x += rhs.x;
			y += rhs.y;
			z += rhs.z;
			w += rhs.w;
			return *this;
		}

		template <typename T>
		inline Vector4<T>& Vector4<T>::operator-=(const Vector4<T>& rhs) {
			x -= rhs.x;
			y -= rhs.y;
			z -= rhs.z;
			w -= rhs.w;
			return *this;
		}

		template <typename T>
		inline Vector4<T>& Vector4<T>::operator*=(const Vector4<T>& rhs) {
			x *= rhs.x;
			y *= rhs.y;
			z *= rhs.z;
			w *= rhs.w;
			return *this;
		}

		template <typename T>
		inline Vector4<T>& Vector4<T>::operator/=(const Vector4<T>& rhs) {
			x /= rhs.x;
			y /= rhs.y;
			z /= rhs.z;
			w /= rhs.w;
			return *this;
		}

		template <typename T>
		inline Vector4<T>& Vector4<T>::operator*=(const T& rhs) {
			x *= rhs;
			y *= rhs;
			z *= rhs;
			w *= rhs;
			return *this;
		}

		template <typename T>
		inline Vector4<T>& Vector4<T>::operator/=(const T& rhs) {
			x /= rhs;
			y /= rhs;
			z /= rhs;
			w /= rhs;
			return *this;
		}

		// Indexer
		template <typename T>
		inline const T& Vector4<T>::operator[](unsigned int i) const {
			SANI_ASSERT(i < Components);
			return (&x)[i];
		}

		template <typename T>
		inline T& Vector4<T>::operator[](unsigned int i) {
			return const_cast<T&>(
				static_cast<const Vector4<T>&>(*this)[i]);
		}
	}
}