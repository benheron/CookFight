#pragma once
#include "TimeTracker.h"

class Timer : public TimeTracker 
{
public:

	Timer(float mins = 0.f, float secs = 0.f, float milSecs = 0.f);
	~Timer();

	void update(float dt);

	void setTimer(float mins = 0.f, float secs = 0.f, float milSecs = 0.f);

	
	float getTimeLeft() { return timeLeft; }

	bool getTimerFinished() { return timerFinished; }

protected:
	
	float timerInput;

	float timeLeft;

	bool timerFinished;

};