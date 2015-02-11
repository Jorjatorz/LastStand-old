#pragma once

#include "EventListener.h"

class Pruebas: public EventListener
{
public:
	Pruebas();
	~Pruebas();

	void onKeyDownEvent(const KeyboardEvent* eventTriggered);
	void onKeyUpEvent(const KeyboardEvent* eventTriggered);
	void onFrameStartedEvent();
};

