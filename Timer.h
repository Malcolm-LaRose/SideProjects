// Timer.h
#pragma once

#ifndef TIMER_H
#define TIMER_H


#include <chrono>
#include <sstream>
#include <iostream>
#include <thread>


class MyTimer {
public:
	// Default Constructor
	MyTimer() : startTime(std::chrono::high_resolution_clock::now()), isStarted(false) {}



	void start() {
		isStarted = true;

		startTime = std::chrono::high_resolution_clock::now();
	}

	void stop() {
		isStarted = false;

		// startTime = std::chrono::high_resolution_clock::now();
	}

	std::chrono::milliseconds getElapsedTimeChrono() {
	
		if (isStarted) {
			auto now = std::chrono::high_resolution_clock::now();
			auto duration = std::chrono::duration_cast<std::chrono::milliseconds>(now - startTime);

			return duration;
		}
	}

	uint32_t getElapsedTimeInt() {
	
		if (isStarted) {
			auto now = std::chrono::high_resolution_clock::now();
			auto duration = std::chrono::duration_cast<std::chrono::milliseconds>(now - startTime);

			return static_cast<uint32_t>(duration.count());
		}

		return 0;
	
	}

	bool started() {
		return isStarted;
	}

	void now() {
		
		startTime = std::chrono::high_resolution_clock::now();

	}



private:
	bool isStarted;
	std::chrono::time_point<std::chrono::high_resolution_clock> startTime; // Time point??

	// uint32_t elapsedTimeInt
	// std::chrono::milliseconds elapsedTimeChrono // --> More literal number with extra steps 

};

//MyTimer initTimer() {
//	MyTimer timer;
//	timer.start();
//
//	return timer;
//
//}



//int main() {
//
//	MyTimer timer;
//
//	bool quit = false;
//	std::stringstream output;
//
//	int countedFrames = 0;
//	timer.start();
//	double avgFPS = 0;
//
//	while (!quit) {
//
//		auto elapsedTime = timer.getElapsedTimeChrono().count();
//		
//		// Update average FPS every 1/5 second
//		if (elapsedTime >= 200) {
//			avgFPS = countedFrames / elapsedTime;
//			countedFrames = 0;
//			timer.start();
//
//			std::cout << "\rAvg FPS: " << (avgFPS) << std::flush;
//		}
//
//		countedFrames++;
//
//	}
//
//	return 0;
//}

#endif // TIMER_H