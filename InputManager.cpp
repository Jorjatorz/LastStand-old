#include "InputManager.h"

#include "MouseEvent.h"
#include "KeyboardEvent.h"
#include "EventManager.h"
#include "Root.h"

InputManager::InputManager(SDL_Window* SDLWindow)
	:mSDLWindowPtr(SDLWindow)
{
	//Initialize all the keys to unpressed
	foreach(elem, mKeyPressedArray)
	{
		*elem = false;
	}
	//Same with mouse
	foreach(elem, mMouseState.mMousePressedArray)
	{
		*elem = false;
	}
	mMouseState.mouseX = mMouseState.mouseY = 0;
	mMouseState.mouseXVariation = mMouseState.mouseYVariation = 0;

	SDL_SetRelativeMouseMode(SDL_TRUE);
}


InputManager::~InputManager()
{
}

void InputManager::processInputEvents()
{
	SDL_Event mEvent;
	EventManager* eventManagerPtr = EventManager::getSingleton();
	while (SDL_PollEvent(&mEvent))
	{
		if (mEvent.type == SDL_QUIT)
		{
			Root::getSingleton()->stopEngine();
			break;
		}

		if (mEvent.type == SDL_MOUSEMOTION)
		{
			mMouseState.mouseX = mEvent.motion.x;
			mMouseState.mouseY = mEvent.motion.y;
			
			mMouseState.mouseXVariation = mEvent.motion.xrel;
			mMouseState.mouseYVariation = mEvent.motion.yrel;

			//Create the mouse event
			MouseEvent mouseEvent = MouseEvent(mMouseState.mouseX, mMouseState.mouseY, mMouseState.mouseXVariation, mMouseState.mouseYVariation, mEvent.button.button, MouseEvent::MOUSE_MOTION);
			eventManagerPtr->mouseEvent(&mouseEvent);
		}

		if (mEvent.type == SDL_MOUSEBUTTONDOWN)
		{
			mMouseState.mMousePressedArray[mEvent.button.button - 1] = true; //-1 to pass from sdl encoding to array acces encoding
			//Create the mouse event
			MouseEvent mouseEvent = MouseEvent(mMouseState.mouseX, mMouseState.mouseY, mMouseState.mouseXVariation, mMouseState.mouseYVariation, mEvent.button.button, MouseEvent::BUTTON_DOWN); //Same coordinates for old X and Y. They haven't changed
			eventManagerPtr->mouseEvent(&mouseEvent);
		}

		if (mEvent.type == SDL_MOUSEBUTTONUP)
		{
			mMouseState.mMousePressedArray[mEvent.button.button - 1] = false;
			//Create the mouse event
			MouseEvent mouseEvent = MouseEvent(mMouseState.mouseX, mMouseState.mouseY, mMouseState.mouseXVariation, mMouseState.mouseYVariation, mEvent.button.button, MouseEvent::BUTTON_UP);
			eventManagerPtr->mouseEvent(&mouseEvent);
		}

		if (mEvent.type == SDL_KEYDOWN)
		{
			mKeyPressedArray[mEvent.key.keysym.scancode] = true;
			//Create and throw the event
			KeyboardEvent keyEvent = KeyboardEvent(mEvent.key.keysym.scancode);
			eventManagerPtr->keyDownEvent(&keyEvent);
		}

		if (mEvent.type == SDL_KEYUP)
		{
			mKeyPressedArray[mEvent.key.keysym.scancode] = false;
			//Create and throw the event
			KeyboardEvent keyEvent = KeyboardEvent(mEvent.key.keysym.scancode);
			eventManagerPtr->keyUpEvent(&keyEvent);
		}
	}
}

void InputManager::resetMousePosition()
{
	SDL_WarpMouseInWindow(mSDLWindowPtr, 540, 360);
}