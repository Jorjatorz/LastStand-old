#include "EventListener.h"


EventListener::EventListener()
	:mRegistered(false)
{
}


EventListener::~EventListener()
{
}

void EventListener::setRegisteredForEvents(bool reg)
{
	mRegistered = reg;
}

bool EventListener::isRegisteredForEvents()
{
	return mRegistered;
}