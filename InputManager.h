#pragma once

#include "FEngine.h"
#include "Singleton.h"

//Input manager that control all the events from the input hardware
class InputManager: public Singleton<InputManager>
{
	//Array containing all the keys status (false if key not pressed). Initialize to false, use SDL_Scancode
	bool mKeyPressedArray[SDL_NUM_SCANCODES];
	//Struct with all the mouse information
	typedef struct
	{
		bool mMousePressedArray[3]; // 1: left, 2: middle, 3: right
		int mouseX, mouseY;
	} tMouseInputStruct;
	tMouseInputStruct mMouseInput;


public:
	InputManager(SDL_Window* SDLWindow);
	~InputManager();

	//Main function, process all the input events that are in the SDL input queue
	void processInputEvents();

private:
	//SDL staff
	//Pointer to the SDL window created in the RenderWindow, needed for the event event queue
	SDL_Window* mSDLWindowPtr;
};

