#pragma once

#include "FEngine.h"

#include "Event.h"

class KeyboardEvent: public Event
{
public:
	KeyboardEvent(int key);
	~KeyboardEvent();

	const KEYBOARD::tKeyEnum mPressedKey;
};

