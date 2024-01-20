#include "stdafx.h"
#include "Timer.h"

void Timer::Start()
{
	startTime = system_clock::now();
	isRunning = true;
	lastTime = system_clock::now();
}

void Timer::Stop()
{
	endTime = system_clock::now();
}

float Timer::GetElapsedMilliseconds()
{
	time_point<system_clock> t;
	if (isRunning) {
		t = system_clock::now();
	}
	else {
		t = endTime;
	}
	return duration_cast<milliseconds>(t - startTime).count();
	
}

float Timer::GetElapsedSeconds()
{
	return GetElapsedMilliseconds() / 1000.0f;
}

float Timer::GetTimeInterval()
{
	// return time since last gettimeinterval
	float t = duration_cast<milliseconds>(system_clock::now() - lastTime).count() / 1000.0f;
	//lastTime = system_clock::now();


	return t;
}
