#pragma once

#include "FEngine.h"

#include "Timer.h"
#include "Singleton.h"

//Class holding all the timers
class TimerManager: public Singleton<TimerManager>
{
public:
	TimerManager();
	~TimerManager();

	//Updates all the timers one per frame
	void updateAllTimers();

	//Allocate a new timer and return it
	Timer* createTimer(std::string name);
	//Deletes a timer
	void deleteTimer(std::string name);
	//Returns a timer
	Timer* getTimer(std::string name);

private:
	std::unordered_map<std::string, Timer*> mTimerMap;
};

