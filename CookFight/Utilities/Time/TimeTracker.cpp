#include "TimeTracker.h"

TimeTracker::TimeTracker() : timePassed(0.f), timeTrackStarted(false)
{

}

TimeTracker::~TimeTracker()
{

}

void TimeTracker::update(float dt)
{
	if (timeTrackStarted)
	{
		timePassed += dt;
	}
}