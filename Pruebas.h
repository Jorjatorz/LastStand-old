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
	void onFrameEndedEvent();
	void onMouseEvent(const MouseEvent* eventTriggered);

private:
	bool transW, transS, transA, transD;
};

