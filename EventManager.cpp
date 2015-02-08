#include "EventManager.h"

#include "EventListener.h"

EventManager::EventManager()
{
}


EventManager::~EventManager()
{
	mEventListenerList.clear();
}

void EventManager::registerEventListener(EventListener* listener)
{
	listener->setRegisteredForEvents(true);

	mEventListenerList.push_back(listener);
}

void EventManager::keyDownEvent(const KeyboardEvent* eventTriggered)
{
	//Notify to all the listeners
	foreach(listener, mEventListenerList)
	{
		(*listener)->onKeyDownEvent(eventTriggered);
	}
}

void EventManager::keyUpEvent(const KeyboardEvent* eventTriggered)
{
	//Notify to all the listeners
	foreach(listener, mEventListenerList)
	{
		(*listener)->onKeyUpEvent(eventTriggered);
	}
}