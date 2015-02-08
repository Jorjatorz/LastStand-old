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

	//Return the scenemanager
	SceneManager* getSceneManager()
	{
		return mSceneManager;
	}

private:
	//Pointer to the render window (created by the Root)
	RenderWindow* mRenderWindow;
	//Pointer to the ResourceManager (created by the Root)
	ResourceManager* mResourceManagerPtr;
	//Pointer to the SceneManager (created by the Root)
	SceneManager* mSceneManager;
	//Pointer to the renderer (created by the Root)
	Renderer* mRenderer;
	//Pointer to the eventManager (created by the Root)
	EventManager* mEventManager;
};

