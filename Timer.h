#pragma once

#include "FEngine.h"

class Timer
{
public:
	Timer();
	~Timer();

	//Starts the timer (if its already started it resets it)
	void start();
	//Updates the timer, can be called explicitly or aut0matically by the TimerManager
	void update();
	//Pause the timer
	unsigned int pause();
	//Resume the timer
	void resume();
	//Stops the timer
	unsigned int stop();
	//Same as start
	unsigned int reset();

	unsigned int getTimeInMiliseconds();
	float getTimeInSeconds();

private:
	unsigned int mStartTime;
	unsigned int mRealTime;
	unsigned int mPauseTime;
	bool mStarted;
	bool mPaused;
};

