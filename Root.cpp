#include "Root.h"

#include "InputManager.h"
#include "RenderWindow.h"
#include "ResourceManager.h"
#include "SceneManager.h"

Root::Root()
	:mRenderWindow(NULL),
	mResourceManagerPtr(NULL),
	mEngineRunning(false)
{
}


Root::~Root()
{
	delete mSceneManager;
	delete mRenderWindow;
	delete mResourceManagerPtr;

	FE_LOG(FE_LOG::INFO, "Root deleted");
}

RenderWindow* Root::initEngine(std::string windowName)
{
	FE_LOG(FE_LOG::INFO, "Initializing Engine...");
	//Create ResoruceManager singleton
	mResourceManagerPtr = new ResourceManager();

	//Create a new render window with default values
	mRenderWindow = new RenderWindow(windowName, 1080, 720);

	//Create a default scenemanager (change this in a future to different types scenemanager)
	mSceneManager = new SceneManager();

	//Keep running until its false
	mEngineRunning = true;
	FE_LOG(FE_LOG::INFO, "Engine Initialized");

	return mRenderWindow;
}

void Root::runEngine()
{
	while (mEngineRunning)
	{
		//Handle input
		InputManager::getSingleton()->processInputEvents();
		//Swap buffers (RenderWindow)
		mRenderWindow->swapBuffers();
	}
}

void Root::stopEngine()
{
	mEngineRunning = false;
}