#pragma once

#include "FEngine.h"

#include "Event.h"

class MouseEvent: public Event
{
public:
	typedef enum
	{
		BUTTON_NONE, //No button pressed (just mouse motion)

		MOUSE_MOTION,
		BUTTON_DOWN,
		BUTTON_UP
	} tMouseActionEnum;

	MouseEvent(int newX, int newY, int oldX_, int oldY_, int but, tMouseActionEnum action);
	~MouseEvent();

	const MOUSE::tMouseButtonsEnum mButton;
	const tMouseActionEnum mButtonActionType;
	const int x, y;
	const int oldX, oldY;
	const int variationX, variationY;
};