#pragma once

#include "FEngine.h"

class Viewport
{
	//Size variables
	int mOriginX; //Top left X origin
	int mOriginY; //Top left Y origin
	int mWidth; //Biggest X (range 0 - 1)
	int mHeight; //Biggest Y (range 0 - 1)

	//True if the viewport has change and needs an update
	bool isDirty;

	//Clear color
	Vector3 mClearColor;

public:
	Viewport(const int& x, const int& y, const int& width, const int& height, Camera* cam);
	~Viewport();

	//Check if the viewport is dirty and if it's update it.
	void updateViewport();

	//Return the viewmatrix of the camera attached to the viewport
	Matrix4 getViewportCameraMatrix();

	//Change the clear color
	void setClearColor(const Vector3& newColor);

private:
	Camera* mAttachedCamera;
};

