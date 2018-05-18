#include "Timer.h"

Timer::Timer(float mins , float secs, float milSecs) : TimeTracker(), timerFinished(false)
{
	timerInput = mins * 60 + secs + milSecs / 1000;
}

Timer::~Timer()
{

}

void Timer::update(float dt)
{
	TimeTracker::update(dt);

	if (!timerFinished)
	{
		timeLeft = timerInput - timePassed;
		
	}
	
	
	if (timeLeft <= 0.f)
	{
		timerFinished = true;
		timeLeft = 0.f;
	}
	timeValue = timeLeft;
}

void Timer::setTimer(float mins, float secs, float milSecs)
{
	timerInput = mins * 60 + secs + milSecs / 1000;

	if (timerInput > 0.f)
	{
		timerFinished = false;
		timePassed = 0.f;
	}
}