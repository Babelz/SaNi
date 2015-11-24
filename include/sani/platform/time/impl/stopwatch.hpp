#include "sani/platform/time/stopwatch.hpp"
#include <stdexcept>

namespace sani {
	
	template<typename T>
	Stopwatch<T>::Stopwatch() : startTime(Timer::now()),
								endTime(Timer::now()),
								running(false) {
	}

	template<typename T>
	bool Stopwatch<T>::isRunning() const {
		return running;
	}

	template<typename T>
	void Stopwatch<T>::reset() {
		startTime = Clock::now();
		endTime = Clock::now();
	}
	template<typename T>
	void Stopwatch<T>::start() {
		if (running) throw std::runtime_error("watch is already measuring");

		running = true;

		reset();
	}
	template<typename T>
	void Stopwatch<T>::stop() {
		if (!running) throw std::runtime_error("watch is not measuring");
		
		running = false;

		endTime = Clock::now();
	}

	template<typename T>
	const Time<T>& Stopwatch<T>::getStartTime() const {
		return startTime;
	}
	template<typename T>
	const Time<T>& Stopwatch<T>::getEndTime() const {
		return endTime;
	}

	template<typename T>
	Stopwatch<T>::~Stopwatch() {
	}
}