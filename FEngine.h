//All the classes

#pragma once

#include <assert.h>
#include <iostream>
#include <string>
#include <vector>
#include <Windows.h>

#include <SDL.h>
#include <gl\glew.h>
#include <gl\gl.h>

//Custom engine includes
#include "FE_LOG.h"
#include "Vector3.h"

class InputManager;
class RenderWindow;
class Root;
class Viewport;



//Defines
//
//
/*Iterator for vectors and list (old)
#define foreach(elem, container) for(auto elem: container)*/
//Foreach element in the container
#define foreach(elem, container) for(auto elem = std::begin(container); elem < std::end(container); ++elem)



//
//