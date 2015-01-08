#pragma once

#include "FEngine.h"
#include "Singleton.h"

class Root: public Singleton<Root>
{
	//True if the engine is running
	bool mEngineRunning;
public:
	Root();
	~Root();

	//Initialize all the components and creates a new window
	RenderWindow* initEngine(std::string windowName);
	//Process the events and render the buffers
	void runEngine();
	//Stops the engine(exit the main loop)
	void stopEngine();

private:
	//Pointer to the render window
	RenderWindow* mRenderWindow;
};

