#include "MouseEvent.h"

MouseEvent::MouseEvent(int newX, int newY, int oldX_, int oldY_, int but, tMouseActionEnum action)
	:x(newX),
	y(newY),
	oldX(oldX_),
	oldY(oldY_),
	mButton(static_cast<MOUSE::tMouseButtonsEnum>(but)),
	variationX(x - oldX),
	variationY(y - oldY),
	mButtonActionType(action)
{
}


MouseEvent::~MouseEvent()
{
}
