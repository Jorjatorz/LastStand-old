#pragma once

#include "FEngine.h"

class RenderWindow
{
	//Variables
	std::string mName;
	int mWidth;
	int mHeight;

	//Viewport list
	std::vector<Viewport*> mViewportList;

public:
	RenderWindow(std::string windowName, int width, int height);
	~RenderWindow();

	//Creates and add a viewport to the RenderWindow
	Viewport* addViewport(int originX = 0, int originY = 0, int width = 1, int height = 1);

private:
	//SDL Staff
	SDL_Window* mSDLWindow;
	SDL_GLContext mSDL_GL_Context;
};

