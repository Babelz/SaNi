#include "sani/platform/time/stopwatch.hpp"
#include <stdexcept>
#include <chrono>

namespace sani {
	
	template<typename T>
	Stopwatch<T>::Stopwatch() : startTime(sani::Clock::now()),
								endTime(sani::Clock::now()),
								running(false) {
	}

	template<typename T>
	bool Stopwatch<T>::isRunning() const {
		return running;
	}

	template<typename T>
	void Stopwatch<T>::restart() {
		reset();

		running = false;

		start();
	}

	template<typename T>
	void Stopwatch<T>::reset() {
		startTime = sani::Clock::now();
		endTime = sani::Clock::now();
	}
	template<typename T>
	void Stopwatch<T>::start() {
		if (running) throw std::runtime_error("watch is already measuring");

		running = true;
	}
	template<typename T>
	void Stopwatch<T>::stop() {
		if (!running) throw std::runtime_error("watch is not measuring");
		
		running = false;

		endTime = sani::Clock::now();
	}

	template<typename T>
	T Stopwatch<T>::getElapsedMilliseconds() const {
		auto delta = endTime - startTime;

		auto elapsed = std::chrono::duration_cast<std::chrono::milliseconds>(delta);

		return static_cast<T>(elapsed.count());
	}
	template<typename T>
	T Stopwatch<T>::getElapsedSeconds() const {
		const T millis = getElapsedMilliseconds();

		return millis * 0.001f;
	}

	template<typename T>
	Stopwatch<T>::~Stopwatch() {
	}
}