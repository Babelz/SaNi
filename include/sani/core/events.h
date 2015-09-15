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
	class EventHandler;

	/// @class CallbackManager "sani\events.hpp"
	///
	/// Generic event-callback manager class.
	template <typename T>
	class CallbackManager {
	friend class EventHandler<T>;
	private:
		std::list<std::function<T>> callbacks;
	public:
		CallbackManager() {
		}

		/// Adds new callback to the callback list.
		template <typename T>
		inline void subscribe(std::function<T> callback) {
			callbacks.push_back(callback);
		}
		/// Removes given callback from the callback list.
		template <typename T>
		inline void unsubscribe(std::function<T> callback) {
			callbacks.remove(callback);
		}
		/// Returns true if the manager contains callbacks.
		inline bool hasSubscribers() const {
			return !callbacks.empty();
		}
	
		~CallbackManager() {
		}

		template <typename T>
		void operator += (std::function<T> callback) {
			callbacks.push_back(callback);
		}
		template <typename T>
		void operator -= (std::function<T> callback) {
			callbacks.remove(callback);
		}
	};

	/// @class EventHandler "sani\events.hpp"
	///
	/// Represents a general, generic event-handler.
	template<typename T>
	class EventHandler {	
	private:
		const CallbackManager<T>* callbackManager;
	public:
		EventHandler(const CallbackManager<T>* callbackManager) : callbackManager(callbackManager) {
		}
		EventHandler() : callbackManager(nullptr) {
		}

		~EventHandler() {
		}

		template <typename T>
		void operator()(std::function<void(std::function<T>)> action) {
			if (!callbackManager->hasSubscribers()) return;

			for (std::function<T> callback : callbackManager->callbacks) action(callback);
		}
	};

	// Macros for creating and initializing events.
	// These macros should be called in the public declaration
	// area of the class.
	#define SANI_DECLARE_EVENT(name, signature) 			private: sani::EventHandler<signature> name##EventHandler; \
															public:  sani::CallbackManager<signature> name		       \

	// Initializes given event with given signature.
	#define SANI_INIT_EVENT(name, signature)				name##EventHandler = sani::EventHandler<signature>(&name)

	#define SANI_CALLBACK(signature, callback)				std::function<signature>(callback)
	
	// Triggers the given event with given signature and passes given args to it.
	#define SANI_TRIGGER_EVENT(name, signature, args)		name##EventHandler(std::function<void(std::function<signature>)>([args](std::function<signature> action) { action(args); }))
	
	// Triggers the given event with given signature and passes no arguments to it.
	#define SANI_TRIGGER_VOID_EVENT(name, signature)		name##EventHandler(std::function<void(std::function<signature>)>([](std::function<signature> action) { action(); }))
}