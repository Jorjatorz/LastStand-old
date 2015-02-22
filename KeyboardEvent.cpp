#include "KeyboardEvent.h"


KeyboardEvent::KeyboardEvent(int key)
	:mPressedKey((KEYBOARD::tKeysEnum)key)
{
}


KeyboardEvent::~KeyboardEvent()
{
}
