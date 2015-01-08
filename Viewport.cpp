#include "Viewport.h"


Viewport::Viewport(int x, int y, int width, int height)
	:mOriginX(x),
	mOriginY(y),
	mWidth(width),
	mHeight(height),
	isDirty(true),
	mClearColor(1.0) //White
{
}


Viewport::~Viewport()
{
}
