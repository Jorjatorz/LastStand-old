#include "MouseEvent.h"

MouseEvent::MouseEvent(int newX, int newY, int xVar, int yVar, int button, tMouseActionEnum action)
	:x(newX),
	y(newY),
	mButton(static_cast<MOUSE::tMouseButtonsEnum>(button)),
	xVariation(xVar),
	yVariation(yVar),
	mButtonActionType(action)
{
}


MouseEvent::~MouseEvent()
{
}
