#pragma once
#include "TimeTracker.h"

class Stopwatch : public TimeTracker
{
public:
	Stopwatch();
	~Stopwatch();

	void update(float dt);


private:


};