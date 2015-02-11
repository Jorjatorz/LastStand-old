#include "Timer.h"


Timer::Timer()
	:mStartTime(0),
	mRealTime(0),
	mStarted(false),
	mPaused(false)
{
}


Timer::~Timer()
{
}


void Timer::start()
{
	//Start/Reset it
	mStartTime = SDL_GetTicks();
	mStarted = true;
	mPaused = false;
}

unsigned int Timer::reset()
{
	update();

	//Reset it
	mStartTime = SDL_GetTicks();
	mStarted = true;
	mPaused = false;

	return mRealTime;
}

void Timer::update()
{
	if (mStarted && !mPaused)
	{
		mRealTime = SDL_GetTicks() - mStartTime;
	}
}

unsigned int Timer::pause()
{
	update();
	mPaused = true;

	return mRealTime;
}

void Timer::resume()
{
	if (mPaused)
	{
		mStartTime = SDL_GetTicks() - mRealTime;
		update();
		mPaused = false;
	}
}

unsigned int Timer::stop()
{
	if (mStarted)
	{
		update();
		mStarted = false;
	}

	return mRealTime;
}

unsigned int Timer::getTimeInMiliseconds()
{
	update();

	return mRealTime;
}

float Timer::getTimeInSeconds()
{
	update();

	return mRealTime / 1000;
}