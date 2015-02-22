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
	//FOR FUTURE, CHECK IF THE LISTENER ALREADY EXISTS
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

void EventManager::mouseEvent(const MouseEvent* eventTriggered)
{
	//Notify to all the listeners
	foreach(listener, mEventListenerList)
	{
		(*listener)->onMouseEvent(eventTriggered);
	}
}


void EventManager::frameStartedEvent()
{
	//Notify to all the listeners
	foreach(listener, mEventListenerList)
	{
		(*listener)->onFrameStartedEvent();
	}
}

void EventManager::frameEndededEvent()
{
	//Notify to all the listeners
	foreach(listener, mEventListenerList)
	{
		(*listener)->onFrameEndedEvent();
	}
}