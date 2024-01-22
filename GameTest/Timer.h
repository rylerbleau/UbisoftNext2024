#pragma once
#include <iostream>
#include <chrono>
#include <ctime>

using namespace std::chrono;
class Timer
{
private:
	time_point<system_clock> startTime;
	time_point<system_clock> endTime;

	bool isRunning = false;
	time_point<system_clock> lastTime;
	float intervalMilliseconds;

public:
	void Start();
	void Stop();
	float GetElapsedMilliseconds();
	float GetElapsedSeconds();
	float GetTimeInterval();
	void ResetTimeInterval() { lastTime = system_clock::now(); }

};

