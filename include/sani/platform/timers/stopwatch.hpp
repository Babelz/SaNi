#pragma once

#include <chrono>

namespace sani {

	typedef std::chrono::high_resolution_clock		Timer;
	
	template<typename T>
	typedef std::chrono::time_point<T>				Time;

	/// @class Stopwatch stopwatch.hpp "sani/platform/timers/stopwatch.hpp"
	/// @author voidbab
	///
	/// Basic high-resolution timer.
	template<typename T>
	class Stopwatch {
	private:
		Time<T> startTime;
		Time<T> endTime;

		bool running;
	public:
		/// Creates new instance of the stopwatch.
		Stopwatch();
		
		/// Returns true if the watch is measuring time.
		bool isRunning() const;
		
		/// Resets the state of the watch.
		void reset();
		/// Starts measuring time.
		void start();
		/// Stops measuring time.
		void stop();

		/// Returns the time when start was last called.
		template<typename T>
		const Time<T>& getStartTime() const;
		/// Returns the time stop was last called.
		template<typename T>
		const Time<T>& getEndTime() const;
		
		~Stopwatch();
	};
}