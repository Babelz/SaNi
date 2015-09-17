#pragma once

#include <cmath>
namespace sani {
	namespace math {
		template <typename T>
		T radians(const T& degrees) {
			// pi / 180 = 0,01745329251994329576923690768489
			return degrees * static_cast<T>(0.01745329251994329576923690768489);
		}

		template <typename T>
		T degrees(const T& radians) {
			// 180 / pi = 57,295779513082320876798154814105
			return radians * static_cast<T>(57.295779513082320876798154814105);
		}

		template<typename T>
		T sin(const T& angle) {
			return std::sin(angle);
		}

		template<typename T>
		T cos(const T& angle) {
			return std::cos(angle);
		}

		template<typename T>
		T tan(const T& angle) {
			return std::tan(angle);
		}

		template<typename T>
		T asin(const T& x) {
			return std::asin(x);
		}

		template<typename T>
		T acos(const T& x) {
			return std::acos(x);
		}

		template<typename T>
		T atan(const T& y, const T& x) {
			return std::atan2(y, x);
		}

		template<typename T>
		T atan(const T& yx) {
			return std::atan(yx);
		}
	}
}

