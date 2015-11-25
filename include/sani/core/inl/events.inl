#include "sani/core/events.hpp"

namespace sani {

	/*
		Event class impl.
	*/

	template<typename T>
	Event<T>::Event() {
	}

	template<typename T>
	void Event<T>::subscribe(std::function<T> callback) {
		callbacks.push_back(callback);
	}
	template<typename T>
	void Event<T>::unsubscribe(std::function<T> callback) {
		if (callbacks.size() == 0) return;

		for (auto i = callbacks.begin(); i != callbacks.end(); i++) {
			if ((*i).template target<T>() == callback.template target<T>()) {
				callbacks.erase(i);

				return;
			}
		}
	}
	
	template<typename T>
	bool Event<T>::hasSubscribers() const {
		return !callbacks.empty();
	}

	template<typename T>
	Event<T>::~Event() {
	}

	template<typename T>
	void Event<T>::operator += (std::function<T> callback) {
		callbacks.push_back(callback);
	}

	template<typename T>
	void Event<T>::operator -= (std::function<T> callback) {
		unsubscribe(callback);
	}

	/*
		EventCaller class impl.
	*/

	template<typename T>
	EventCaller<T>::EventCaller(const Event<T>* event) : event(event) {
	}
	template<typename T>
	EventCaller<T>::EventCaller() : event(nullptr) {
	}

	template<typename T>
	EventCaller<T>::~EventCaller() {
	}

	template<typename T>
	void EventCaller<T>::operator() (std::function<void(std::function<T>)> action) {
		if (!event->hasSubscribers()) return;

		for (std::function<T> callback : event->callbacks) action(callback);
	}
}