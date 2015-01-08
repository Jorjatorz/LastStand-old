#include "Viewport.h"


Viewport::Viewport(const int& x, const int& y, const int& width, const int& height)
	:mOriginX(x),
	mOriginY(y),
	mWidth(width),
	mHeight(height),
	isDirty(true),
	mClearColor(0.5) //Grey
{
}


Viewport::~Viewport()
{
}

void Viewport::updateViewport()
{
	if (isDirty)
	{
		glScissor(mOriginX, mOriginY, mWidth, mHeight);
		glViewport(mOriginX, mOriginY, mWidth, mHeight);
		glClearColor(mClearColor.r, mClearColor.g, mClearColor.b, 1.0);

		isDirty = false;
	}
}

void Viewport::setClearColor(const Vector3& newColor)
{
	mClearColor = newColor;
	isDirty = true;
}