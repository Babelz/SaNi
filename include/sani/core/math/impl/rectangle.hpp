#pragma once

#include "../rectangle.hpp"

namespace sani {
	namespace math {

			template <typename T>
			template <typename U>
			Rectangle<T>::Rectangle(const U x, const U y, const U h, const U w) : x(static_cast<T>(x)),
																				  y(static_cast<T>(y)),
																				  h(static_cast<T>(h)),
																				  w(static_cast<T>(w)) {
			}
			
			template <typename T>
			Rectangle<T>::Rectangle(const T x, const T y, const T h, const T w) : x(x),
																				  y(y),
																				  h(h),
																				  w(w) {
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
				
				v.x = x + (w / 2);
				v.y = y + (h / 2);

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
			void Rectangle<T>::center(Vector2<T>& v) const {
				v.x = x + (w / 2);
				v.y = y + (h / 2);
			}

			template <typename T>
			void Rectangle<T>::position(Vector2<T>& v) const {
				v.x = x;
				v.y = y;
			}
			
			template <typename T>
			void Rectangle<T>::size(Vector2<T>& v) const {
				v.x = w;
				v.y = h;
			}

			template <typename T>
			bool Rectangle<T>::isEmpty() const {
				return x == 0 && y == 0 && h == 0 && w == 0;
			}

			template <typename T>
			bool Rectangle<T>::contains(const T x, const T y) const {
				return ((((this->x <= x) && x < (this->x + this->w))) && (this->y <= y) && (y < (this->y + this->h)));
			}
			
			template <typename T>
			bool Rectangle<T>::contains(const sani::math::Vector2<T>& v) const {
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

