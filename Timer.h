// Timer.h
#pragma once

#ifndef TIMER_H
#define TIMER_H


#include <chrono>
#include <sstream>
#include <iostream>
#include <thread>


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

	void logFPS() {
		computeFrameDuration();

		auto currentTime = t_now();
		if (currentTime - outputTime >= std::chrono::microseconds(250000)) {
			system("cls");
			std::cout << "\rFPS: " << (1000000.0 / frameDuration.count()) << std::endl; // Print FPS
			std::cout << "\rFRAME TIME: " << frameDuration.count() << std::flush; // Print frame time
			std::cout << std::endl; // Move to the next line

			outputTime = currentTime; // Update output time
		}
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

	std::chrono::duration<double, std::micro> getTotalTimeElapsed() {
		return t_now() - startTime; // Time between now and program start
	}

	std::chrono::duration<double, std::micro>  getOutputTimeElapsed() {
		return t_now() - outputTime;
	}

};

#endif // TIMER_H