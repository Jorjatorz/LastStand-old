#include "InputManager.h"

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
	foreach(elem, mMouseInput.mMousePressedArray)
	{
		*elem = false;
	}
	mMouseInput.mouseX = mMouseInput.mouseY = 0.0;
}


InputManager::~InputManager()
{
}

void InputManager::processInputEvents()
{
	SDL_Event mEvent;
	while (SDL_PollEvent(&mEvent))
	{
		if (mEvent.type == SDL_QUIT)
		{
			Root::getSingleton()->stopEngine();
			break;
		}

		if (mEvent.type == SDL_MOUSEMOTION)
		{
			SDL_GetMouseState(&mMouseInput.mouseX, &mMouseInput.mouseY);
		}

		if (mEvent.type == SDL_MOUSEBUTTONDOWN)
		{
			mMouseInput.mMousePressedArray[mEvent.button.button - 1] = true; //-1 to pass from sdl encoding to array acces encoding
		}

		if (mEvent.type == SDL_MOUSEBUTTONUP)
		{
			mMouseInput.mMousePressedArray[mEvent.button.button - 1] = false;
		}

		if (mEvent.type == SDL_KEYDOWN)
			mKeyPressedArray[mEvent.key.keysym.scancode] = true;

		if (mEvent.type == SDL_KEYUP)
			mKeyPressedArray[mEvent.key.keysym.scancode] = false;
	}
}