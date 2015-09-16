#pragma once

#include "sani/precompiled.hpp"
#include <list>
#include <functional>

/*
	To create an event...
		SANI_DECLARE_EVENT(name, signature);

		example
		SANI_DECLARE_EVENT(onClosed, void(void));

	To initialize the event..
		SANI_INIT_EVENT(name, signature);

		example
		SANI_INIT_EVENT(onClosed, void(void));

	To call the event from the class that owns it
		SANI_TRIGGER_VOID_EVENT(name, signature)
		SANI_TRIGGER_EVENT(name, signature, args)

		example
		SANI_TRIGGER_VOID_EVENT(onClosed, void(void));
		SANI_TRIGGER_EVENT(onCallback, void(void*), status);
*/

namespace sani {

	template <typename T>
	class EventCaller;

	/// @class CallbackManager "sani\events.hpp"
	///
	/// Generic event-callback manager class.
	template <typename T>
	class Event {
	friend class EventCaller<T>;
	private:
		std::list<std::function<T>> callbacks;
	public:
		Event() {
		}

		/// Adds new callback to the callback list.
		inline void subscribe(std::function<T> callback) {
			callbacks.push_back(callback);
		}
		/// Removes given callback from the callback list.
		inline void unsubscribe(std::function<T> callback) {
			if (callbacks.size() == 0) return;

			for (auto i = callbacks.begin(); i != callbacks.end(); i++) {
				if ((*i).target<T>() == callback.target<T>()) {
					callbacks.erase(i);
					
					return;
				}
			}
		}
		/// Returns true if the manager contains callbacks.
		inline bool hasSubscribers() const {
			return !callbacks.empty();
		}
	
		~Event() {
		}

		void operator += (std::function<T> callback) {
			callbacks.push_back(callback);
		}

		void operator -= (std::function<T> callback) {
			unsubscribe(callback);
		}
	};

	/// @class EventHandler "sani\events.hpp"
	///
	/// Represents a general, generic event-handler.
	template<typename T>
	class EventCaller {	
	private:
		const Event<T>* event;
	public:
		EventCaller(const Event<T>* event) : event(event) {
		}
		EventCaller() : event(nullptr) {
		}

		~EventCaller() {
		}

		void operator()(std::function<void(std::function<T>)> action) {
			if (!event->hasSubscribers()) return;

			for (std::function<T> callback : event->callbacks) action(callback);
		}
	};

	// Macros for creating and initializing events.
	// These macros should be called in the public declaration
	// area of the class.
	#define SANI_DECLARE_EVENT(name, signature) 			private: sani::EventCaller<signature> name##Caller; \
															public:  sani::Event<signature> name		        \

	// Initializes given event with given signature.
	#define SANI_INIT_EVENT(name, signature)				name##Caller = sani::EventCaller<signature>(&name)

	#define SANI_EVENT_HANDLER(signature, callback)			std::function<signature>(callback)
	
	// Triggers the given event with given signature and passes given args to it.
	#define SANI_TRIGGER_EVENT(name, signature, args)		name##Caller(std::function<void(std::function<signature>)>([args](std::function<signature> action) { action(args); }))
	
	// Triggers the given event with given signature and passes no arguments to it.
	#define SANI_TRIGGER_VOID_EVENT(name, signature)		name##Caller(std::function<void(std::function<signature>)>([](std::function<signature> action) { action(); }))
}