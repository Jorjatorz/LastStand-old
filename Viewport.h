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
	Viewport(int x, int y, int width, int height);
	~Viewport();
};

