#include "Root.h"

#include "EventManager.h"
#include "InputManager.h"
#include "Renderer.h"
#include "RenderWindow.h"
#include "ResourceManager.h"
#include "SceneManager.h"
#include "TimerManager.h"

Root::Root()
	:mRenderWindow(NULL),
	mRenderer(NULL),
	mResourceManagerPtr(NULL),
	mEventManager(NULL),
	mSceneManager(NULL),
	mTimerManager(NULL),
	mEngineRunning(false),
	mLastFrameDelay(0)
{
}


Root::~Root()
{
	FE_LOG(FE_LOG::INFO, "Time the engine has being executed: %f seconds", mEngineTimer->stop() / 1000.0);

	delete mTimerManager;
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

	//Create the timer manager
	mTimerManager = new TimerManager();

	//Keep running until its false
	mEngineRunning = true;

	//Create the engine counter
	mEngineTimer = mTimerManager->createTimer("EngineTimer");
	//Start the timer
	mEngineTimer->start();

	FE_LOG(FE_LOG::INFO, "Engine Initialized");

	return mRenderWindow;
}

void Root::runEngine()
{
	int frames = 0;
	int deltaTime = 0;

	Timer deltaTimeTimer; //Stack timer that computes the delta time of each frame

	while (mEngineRunning)
	{
		deltaTimeTimer.start();

		//Update the timers
		TimerManager::getSingleton()->updateAllTimers();

		//Handle input
		InputManager::getSingleton()->processInputEvents();

		//Process all the nodes in the scene
		mSceneManager->processRootSceneNode();

		//Swap buffers (RenderWindow)
		mEventManager->frameStartedEvent();
		mRenderWindow->swapBuffers();
		mEventManager->frameEndededEvent();

		//Calculate fps
		frames++;
		mLastFrameDelay = deltaTimeTimer.getTimeInMiliseconds();
		deltaTime += deltaTimeTimer.reset();

		//std::cout << deltaTime << std::endl;

		if (deltaTime >= 1000)
		{
			std::cout << frames << std::endl;
			frames = 0;
			deltaTime = 0;
		}
	}
}

void Root::stopEngine()
{
	mEngineRunning = false;
}