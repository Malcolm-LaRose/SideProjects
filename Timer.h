// Timer.h
#pragma once

#ifndef TIMER_H
#define TIMER_H


#include <chrono>
#include <sstream>
#include <iostream>
#include <thread>
#include <cmath>


class MyTimer_us {
public:

	MyTimer_us() : // Multi line constructor
		startTime(std::chrono::steady_clock::now()), // Init with current time --> Class should be init'ed right before main loop
		frameBeginTime(std::chrono::steady_clock::now()), // Init with current time, will be changed immediately
		frameEndTime(std::chrono::steady_clock::now()) // Init with current time, will be changed immediately
	{
		outputTime = startTime;
	}


	void markFrameBeginTime() {
		frameBeginTime = t_now();
	}
	void markFrameEndTime() {
		frameEndTime = t_now();
	}

	void logFPS() { // SEEMS TO BE BROKEN !!!
		computeFrameDuration();

		auto currentTime = t_now();
		if (currentTime - outputTime >= std::chrono::microseconds(200000)) {
			system("cls");
			std::cout << "\rFPS: " << getFPS() << std::endl; // Print FPS
			std::cout << "\rFRAME TIME: " << getFrameTime_us() << std::endl; // Print frame time

			outputTime = currentTime; // Update output time
		}
	}

	static std::chrono::duration<double, std::micro> getFrameDuration(MyTimer_us* timer) {
		return (*timer).frameDuration;
	}

	static void capFPS(int fpscap, std::chrono::duration<double, std::micro> frameDuration, MyTimer_us* timer) {
		double desiredFrameDuration = (1000000.0 / fpscap);
		std::chrono::duration<double, std::micro> desiredFD_us = std::chrono::duration<double, std::micro>(desiredFrameDuration); // DONT convert to std::chrono::milliseconds, it doesnt work

		if (frameDuration < desiredFD_us) {
			std::this_thread::sleep_for(desiredFD_us - frameDuration);
		}

	}

	std::chrono::duration<double, std::micro> getTotalTimeElapsed() {
		return t_now() - startTime; // Time between now and program start
	}



private:

	std::chrono::steady_clock::time_point startTime;
	std::chrono::steady_clock::time_point outputTime;
	std::chrono::steady_clock::time_point frameBeginTime;
	std::chrono::steady_clock::time_point frameEndTime;

	std::chrono::duration<double, std::micro> frameDuration;

	void computeFrameDuration() {
		frameDuration = frameEndTime - frameBeginTime;
	}

	std::chrono::steady_clock::time_point t_now() {
		return std::chrono::steady_clock::now(); // Helper function to shorten this line
	}

	std::chrono::duration<double, std::micro>  getOutputTimeElapsed() {
		return t_now() - outputTime;
	}

	double getFPS() {
		return 1000000.0 / frameDuration.count();
	}

	double getFrameTime_us() {
		return frameDuration.count();
	}

};

#endif // TIMER_H