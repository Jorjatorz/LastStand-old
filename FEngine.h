//All the classes

#pragma once

//STL
#include <assert.h>
#include <fstream>
#include <iostream>
#include <list>
#include <deque>
#include <queue>
#include <sstream>
#include <string>
#include <unordered_map>
#include <vector>
#include <Windows.h>

//SDL/OPENGL
#include <SDL.h>
#include <gl\glew.h>
#include <gl\gl.h>

//Custom engine includes
#include "FE_LOG.h"
#include "Matrix4.h"
#include "Quaternion.h"
#include "Vector3.h"

class DeferredFrameBuffer;
class Entity;
class Event;
class EventListener;
class EventManager;
class FrameBuffer;
class InputManager;
class KeyboardEvent;
class Mesh;
class MouseEvent;
class MovableObject;
class Renderer;
class RenderWindow;
class ResourceManager;
class Root;
class SceneManager;
class SceneNode;
class Shader;
class Texture;
class Timer;
class TimerManager;
class Viewport;

//Global enumerations

//Namespace holding all thing related with the keyboard
namespace KEYBOARD
{
	//Corresponds to the SDL scancodes
	typedef enum
	{
		UNKNOWN = 0,

		A = 4,
		B = 5,
		C = 6,
		D = 7,
		E = 8,
		F = 9,
		G = 10,
		H = 11,
		I = 12,
		J = 13,
		K = 14,
		L = 15,
		M = 16,
		N = 17,
		O = 18,
		P = 19,
		Q = 20,
		R = 21,
		S = 22,
		T = 23,
		U = 24,
		V = 25,
		W = 26,
		X = 27,
		Y = 28,
		Z = 29,

		NUM_1 = 30,
		NUM_2 = 31,
		NUM_3 = 32,
		NUM_4 = 33,
		NUM_5 = 34,
		NUM_6 = 35,
		NUM_7 = 36,
		NUM_8 = 37,
		NUM_9 = 38,
		NUM_0 = 39,

		RETURN = 40,
		ESCAPE = 41,
		BACKSPACE = 42,
		TAB = 43,
		SPACE = 44
	} tKeyEnum;
}

//Defines
//
//
/*Iterator for vectors and list (old)
#define foreach(elem, container) for(auto elem: container)*/
//Foreach element in the container
#define foreach(elem, container) for(auto elem = std::begin(container); elem != std::end(container); ++elem)



//
//