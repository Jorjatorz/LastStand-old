#include "Viewport.h"

#include "Camera.h"

Viewport::Viewport(const int& x, const int& y, const int& width, const int& height, Camera* cam)
	:mOriginX(x),
	mOriginY(y),
	mWidth(width),
	mHeight(height),
	isDirty(true),
	mAttachedCamera(cam),
	mClearColor(0.5) //Grey
{
}


Viewport::~Viewport()
{
}

void Viewport::updateViewport()
{
	if (mAttachedCamera == NULL)
	{
		FE_LOG(FE_LOG::ERR, "No camera attached to the viewport");
		assert(0);
	}

	if (isDirty)
	{
		glScissor(mOriginX, mOriginY, mWidth, mHeight);
		glViewport(mOriginX, mOriginY, mWidth, mHeight);
		glClearColor(mClearColor.r, mClearColor.g, mClearColor.b, 1.0);

		isDirty = false;
	}


	//Update the matrix camera
	mAttachedCamera->processViewMatrix();

}

void Viewport::setClearColor(const Vector3& newColor)
{
	mClearColor = newColor;
	isDirty = true;
}

Matrix4 Viewport::getViewportCameraMatrix()
{
	if (mAttachedCamera == NULL)
	{
		FE_LOG(FE_LOG::ERR, "No camera attached to the viewport");
		assert(0);
	}

	return mAttachedCamera->getViewMatrix();
}