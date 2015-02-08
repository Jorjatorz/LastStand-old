#include "Root.h"

#include "EventManager.h"
#include "InputManager.h"
#include "Renderer.h"
#include "RenderWindow.h"
#include "ResourceManager.h"
#include "SceneManager.h"

Root::Root()
	:mRenderWindow(NULL),
	mRenderer(NULL),
	mResourceManagerPtr(NULL),
	mEngineRunning(false)
{
}


Root::~Root()
{
	delete mSceneManager;
	delete mRenderer;
	delete mRenderWindow;
	delete mResourceManagerPtr;
	delete mEventManager;

	FE_LOG(FE_LOG::INFO, "Root deleted");
}

RenderWindow* Root::initEngine(std::string windowName)
{
	FE_LOG(FE_LOG::INFO, "Initializing Engine...");
	//Create the event manager
	mEventManager = new EventManager();

	//Create ResoruceManager singleton
	mResourceManagerPtr = new ResourceManager();

	//Create a new render window with default values
	mRenderWindow = new RenderWindow(windowName, 1080, 720);

	//Create te engine renderer singleton
	mRenderer = new Renderer();

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

		//Process all the nodes in the scene
		mSceneManager->processRootSceneNode();

		//Swap buffers (RenderWindow)
		mRenderWindow->swapBuffers();
	}
}

void Root::stopEngine()
{
	mEngineRunning = false;
}