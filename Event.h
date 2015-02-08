#pragma once

#include "FEngine.h"

//Class holding the event information

class Event
{
public:
	Event();
	~Event();

	//frame time since last frame
	int timeSinceLastFrame;
};

