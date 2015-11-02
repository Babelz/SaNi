#pragma once

namespace sani {
	namespace math {

		template <typename T>
		Vector2<T> normalize(const Vector2<T>& v) {
			return Vector2<T>(v / length(v));
		}

		template <typename T>
		Vector3<T> normalize(const Vector3<T>& v) {
			return Vector3<T>(v / length(v));
		}

		template <typename T>
		Vector4<T> normalize(const Vector4<T>& v) {
			return Vector4<T>(v / length(v));
		}

		template <typename T>
		T length(const Vector2<T>& a) {
			return std::sqrt(dot(a, a));
		}

		template <typename T>
		T length(const Vector3<T>& a) {
			return std::sqrt(dot(a, a));
		}

		template <typename T>
		T length(const Vector4<T>& a) {
			return std::sqrt(dot(a, a));
		}

		template <typename T>
		T length2(const Vector2<T>& a) {
			return dot(a, a);
		}

		template <typename T>
		T length2(const Vector3<T>& a) {
			return dot(a, a);
		}

		template <typename T>
		T length2(const Vector4<T>& a) {
			return dot(a, a);
		}

		template <typename T>
		T dot(const Vector2<T>& a, const Vector2<T>& b) {
			Vector2<T> temp(a * b);
			return temp.x + temp.y;
		}

		template <typename T>
		T dot(const Vector3<T>& a, const Vector3<T>& b) {
			Vector3<T> temp(a * b);
			return temp.x + temp.y + temp.z;
		}

		template <typename T>
		T dot(const Vector4<T>& a, const Vector4<T>& b) {
			Vector4<T> temp(a * b);
			return temp.x + temp.y + temp.z + temp.w;
		}

		template <typename T>
		Vector3<T> cross(const Vector3<T>& a, const Vector3<T>& b) {
			Vector3<T> result;

			result.x = a.y * b.z - a.z * b.z;
			result.y = -(a.x * b.z - a.z * b.x);
			result.z = (a.x * b.y - a.y * b.x);

			return result;
		}
	}
}

