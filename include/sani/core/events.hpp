#pragma once

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
		Event();

		/// Adds new callback to the callback list.
		inline void subscribe(std::function<T> callback);
		/// Removes given callback from the callback list.
		inline void unsubscribe(std::function<T> callback);
		/// Returns true if the manager contains callbacks.
		inline bool hasSubscribers() const;
	
		~Event();

		void operator += (std::function<T> callback);

		void operator -= (std::function<T> callback);
	};

	/// @class EventHandler "sani\events.hpp"
	///
	/// Represents a general, generic event-handler.
	template<typename T>
	class EventCaller {	
	private:
		const Event<T>* event;
	public:
		EventCaller(const Event<T>* e);
		EventCaller();

		~EventCaller();

		void operator () (std::function<void(std::function<T>)> action);
	};

	// Macros for creating and initializing events.
	// These macros should be called in the public declaration
	// area of the class.
	#define SANI_DECLARE_EVENT(name, signature) 			private: EventCaller<signature> name##Caller; \
															public:  Event<signature> name		        \

	// Initializes given event with given signature.
	#define SANI_INIT_EVENT(name, signature)				name##Caller = EventCaller<signature>(&name)

	#define SANI_EVENT_HANDLER(signature, callback)			std::function<signature>(callback)
	
	// Triggers the given event with given signature and passes given args to it.
	#define SANI_TRIGGER_EVENT(name, signature, args)		name##Caller([args](std::function<signature> func) { func(args); })
	
	// Triggers the given event with given signature and passes no arguments to it.
	#define SANI_TRIGGER_VOID_EVENT(name, signature)		name##Caller(std::function<void(std::function<signature>)>([](std::function<signature> action) { action(); }))
}

#include "sani/core/inl/events.inl"