#include "TimerManager.h"

TimerManager::TimerManager()
{
}


TimerManager::~TimerManager()
{
	foreach(timer, mTimerMap)
	{
		delete timer->second;
	}

	mTimerMap.clear();
}

Timer* TimerManager::createTimer(std::string name)
{
	auto it = mTimerMap.find(name);
	if (it != mTimerMap.end())
	{
		FE_LOG(FE_LOG::ERR, "Can't create the timer, it already exist: " + name);
		assert(0);
	}

	Timer* newTimer = new Timer();
	mTimerMap.emplace(std::make_pair(name, newTimer));

	return newTimer;
}

void TimerManager::deleteTimer(std::string name)
{
	auto it = mTimerMap.find(name);
	if (it == mTimerMap.end())
	{
		FE_LOG(FE_LOG::ERR, "Can't delete the timer from memory, it already exist: " + name);
		assert(0);
	}

	delete it->second;
	mTimerMap.erase(it);
}

Timer* TimerManager::getTimer(std::string name)
{
	auto it = mTimerMap.find(name);
	if (it == mTimerMap.end())
	{
		FE_LOG(FE_LOG::ERR, "Can't get the timer in memory, it doesn't exists: " + name);
		assert(0);
	}

	return it->second;
}

void TimerManager::updateAllTimers()
{
	foreach(timer, mTimerMap)
	{
		timer->second->update();
	}
}