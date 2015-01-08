#include "RenderWindow.h"

#include "Viewport.h"
#include "InputManager.h"

RenderWindow::RenderWindow(std::string windowName, int width, int height)
	:mName(windowName),
	mWidth(width),
	mHeight(height)
{

	//inits SDL and GLEW
	SDL_Init(SDL_INIT_EVERYTHING);
	glewExperimental = GL_TRUE;
	glewInit();

	//Set attributes
	SDL_GL_SetAttribute(SDL_GL_RED_SIZE, 8);
	SDL_GL_SetAttribute(SDL_GL_GREEN_SIZE, 8);
	SDL_GL_SetAttribute(SDL_GL_BLUE_SIZE, 8);
	SDL_GL_SetAttribute(SDL_GL_ALPHA_SIZE, 8);
	SDL_GL_SetAttribute(SDL_GL_BUFFER_SIZE, 32);
	SDL_GL_SetAttribute(SDL_GL_DEPTH_SIZE, 24);
	SDL_GL_SetAttribute(SDL_GL_DOUBLEBUFFER, 1);

	//create the window
	mSDLWindow = SDL_CreateWindow(windowName.c_str(), SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, mWidth, mHeight, SDL_WINDOW_OPENGL);
	//create the context
	mSDL_GL_Context = SDL_GL_CreateContext(mSDLWindow);

	//GET INFO
	const char* vendor = reinterpret_cast<const char*>(glGetString(GL_VENDOR));
	const char* version = reinterpret_cast<const char*>(glGetString(GL_VERSION));
	const char* renderer = reinterpret_cast<const char*>(glGetString(GL_RENDERER));
	const char* glslVersion = reinterpret_cast<const char*>(glGetString(GL_SHADING_LANGUAGE_VERSION));
	std::cout << "OpenGL " << version << " initialized." << std::endl;
	std::cout << "(" << vendor << "; " << renderer << ")" << std::endl;
	std::cout << "GLSL version: " << glslVersion << std::endl;

	//Create the imputManager
	InputManager* newInputManagerSingleton = new InputManager(mSDLWindow);

	FE_LOG(FE_LOG::INFO, "Render Window created");
}


RenderWindow::~RenderWindow()
{
	//Delete all the attached viewports
	foreach(viewp, mViewportList)
	{
		delete *viewp;
	}

	//Delete the input manager
	delete InputManager::getSingleton();

	//Delete the context
	SDL_GL_DeleteContext(mSDL_GL_Context);

	//Destroy the window
	SDL_DestroyWindow(mSDLWindow);

	//Stop SDL
	SDL_Quit();

	FE_LOG(FE_LOG::INFO, "Render Window destroyed");
}

Viewport* RenderWindow::addViewport(int originX, int originY, int width, int height)
{
	//Create and save the new viewport
	Viewport* vp = new Viewport(originX, originY, width, height);
	mViewportList.push_back(vp);

	return vp;
}