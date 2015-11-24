#include "sani/platform/time/stopwatch.hpp"
#include <stdexcept>
#include <chrono>

namespace sani {
	
	template<typename T>
	Stopwatch<T>::Stopwatch() : running(false) {
	}

	template<typename T>
	bool Stopwatch<T>::isRunning() const {
		return running;
	}

	template<typename T>
	void Stopwatch<T>::reset() {
		//startTime = sani::Clock::now();
		//endTime = sani::Clock::now();
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

		//endTime = sani::Clock::now();
	}

	template<typename T>
	T Stopwatch<T>::getElapsedMilliseconds() const {
		return T();//std::chrono::duration_cast<std::chrono::milliseconds>(endTime - startTime).;
	}
	template<typename T>
	T Stopwatch<T>::getElapsedSeconds() const {
		return T();//(T)std::chrono::duration_cast<std::chrono::seconds>(endTime - startTime).count();
	}

	template<typename T>
	Stopwatch<T>::~Stopwatch() {
	}
}