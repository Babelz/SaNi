#pragma once

#include "sani/platform/time/time.hpp"

namespace sani {

	/// @class Stopwatch stopwatch.hpp "sani/platform/timers/stopwatch.hpp"
	/// @author voidbab
	///
	/// Basic high-resolution timer.
	template<typename T>
	class Stopwatch {
	private:
		Time startTime;
		Time endTime;

		bool running;
	public:
		/// Creates new instance of the stopwatch.
		Stopwatch();
		
		/// Returns true if the watch is measuring time.
		bool isRunning() const;
		
		/// Resets the state of the watch and starts measuring time.
		void restart();
		/// Resets the state of the watch.
		void reset();
		/// Starts measuring time.
		void start();
		/// Stops measuring time.
		void stop();

		T getElapsedMilliseconds() const;
		T getElapsedSeconds() const;
		
		~Stopwatch();
	};
}

#include "sani/platform/time/impl/stopwatch.hpp"