#pragma once

#include "FEngine.h"

class EventListener
{
public:
	EventListener();
	~EventListener();

	//Set if this Listener is registered for reciving events
	void setRegisteredForEvents(bool reg);
	//Return true if the frame listener is registered in the EventMaanger (so it can recive events)
	bool isRegisteredForEvents();

	//EVENT CALLS
	//key up event occured
	virtual void onKeyDownEvent(const KeyboardEvent* eventTriggered)
	{
	}
	//Key down event occured
	virtual void onKeyUpEvent(const KeyboardEvent* eventTriggered)
	{
	}
	//When a frame is started
	virtual void onFrameStartedEvent()
	{
	}
	//When a frame is ended
	virtual void onFrameEndedEvent()
	{
	}

private:
	bool mRegistered;
};

