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

	//Main function, swaps the buffers
	void swapBuffers();

	//Creates and add a viewport to the RenderWindow
	Viewport* addViewport(const int& originX = 0, const int& originY = 0, const int& width = 1080, const int& height = 720);

private:
	//SDL Staff
	SDL_Window* mSDLWindow;
	SDL_GLContext mSDL_GL_Context;
};

