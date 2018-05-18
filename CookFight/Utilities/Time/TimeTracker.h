#pragma once

class TimeTracker
{
public:
	TimeTracker();
	~TimeTracker();


	virtual void update(float dt);

	void startTrackingTime() { timeTrackStarted = true; }

	void stopTrackingTime() { timeTrackStarted = false; }

	float getTimePassed() { return timePassed; }

	/**
	@brief Get the Time Value from Timer or Stopwatch
	@returns The float value of the time
	*/

	float getTimeValue() { return timeValue; }

protected:
	bool timeTrackStarted;

	float timePassed;


	float timeValue;
};