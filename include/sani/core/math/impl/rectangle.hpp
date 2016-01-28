#pragma once

#include "../rectangle.hpp"

namespace sani {
	namespace math {

			template <typename T>
			template <typename U>
			Rectangle<T>::Rectangle(const U x, const U y, const U w, const U h) : x(static_cast<T>(x)),
																				  y(static_cast<T>(y)),
																				  w(static_cast<T>(w)),
																				  h(static_cast<T>(h)) {
			}
			
			template <typename T>
			Rectangle<T>::Rectangle(const T x, const T y, const T w, const T h) : x(x),
																				  y(y),
																				  w(w),
																				  h(h) {
			}
			
			template <typename T>
			template <typename U>
			Rectangle<T>::Rectangle(const U x, const U y, const U size) : x(static_cast<T>(x)),
																		  y(static_cast<T>(y)),
																		  h(static_cast<T>(size)),
																		  w(static_cast<T>(size)) {
			}

			template <typename T>
			Rectangle<T>::Rectangle(const T x, const T y, const T size) : x(x),
																		  y(y),
																		  h(size),
																		  w(size) {
			}

			template <typename T>
			Rectangle<T>::Rectangle() : x(T()),
										y(T()),
										h(T()),
										w(T()) {
			}

			template <typename T>
			T Rectangle<T>::top() const {
				return y;
			}

			template <typename T>
			T Rectangle<T>::right() const {
				return x + w;
			}

			template <typename T>
			T Rectangle<T>::bottom() const {
				return y + h;
			}

			template <typename T>
			T Rectangle<T>::left() const {
				return x;
			}

			template <typename T>
			Vector2<T> Rectangle<T>::center() const {
				Vector2<T> v;
				
				v.x = x + (w / static_cast<T>(2));
				v.y = y + (h / static_cast<T>(2));

				return v;
			}

			template <typename T>
			Vector2<T> Rectangle<T>::position() const {
				Vector2<T> v;

				v.x = x;
				v.y = y;

				return v;
			}

			template <typename T>
			Vector2<T> Rectangle<T>::size() const {
				Vector2<T> v;

				v.x = w;
				v.y = h;

				return v;
			}

			template <typename T>
			void Rectangle<T>::include(const Vector2<T>& r) {
				x = std::min(x, r.x);
				y = std::min(y, r.y);
				w = std::max(x + w, r.x) - x + T(1);
				h = std::max(y + h, r.y) - y + T(1);
			}

			template <typename T>
			bool Rectangle<T>::isEmpty() const {
				return x == static_cast<T>(0) && y == static_cast<T>(0) && h == static_cast<T>(0) && w == static_cast<T>(0);
			}

			template <typename T>
			bool Rectangle<T>::contains(const T x, const T y) const {
				return ((((this->x <= x) && x < (this->x + this->w))) && (this->y <= y) && (y < (this->y + this->h)));
			}
			
			template <typename T>
			bool Rectangle<T>::contains(const Vector2<T>& v) const {
				return contains(v.x, v.y);
			}

			template <typename T>
			bool Rectangle<T>::intersects(const Rectangle& r) const {
				return r.left() < right() &&
					   left() < r.right() &&
					   r.top() < bottom() &&
					   top() < r.bottom();
			}

			template <typename T>
			bool Rectangle<T>::operator ==(const Rectangle& r) const {
				return r.x == x && r.y == y && r.h == h && r.w == w;
			}
			
			template <typename T>
			bool Rectangle<T>::operator !=(const Rectangle& r) const {
				return !(*this == r);
			}

			template <typename T>
			Rectangle<T>& Rectangle<T>::operator =(const Rectangle& r) {
				if (*this == r) return *this;

				x = r.x;
				y = r.y;
				h = r.h;
				w = r.w;

				return *this;
			}
	}
}

