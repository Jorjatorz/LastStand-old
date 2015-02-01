//All the classes

#pragma once

//STL
#include <assert.h>
#include <fstream>
#include <iostream>
#include <list>
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
class FrameBuffer;
class InputManager;
class Mesh;
class MovableObject;
class Renderer;
class RenderWindow;
class ResourceManager;
class Root;
class SceneManager;
class SceneNode;
class Shader;
class Texture;
class Viewport;



//Defines
//
//
/*Iterator for vectors and list (old)
#define foreach(elem, container) for(auto elem: container)*/
//Foreach element in the container
#define foreach(elem, container) for(auto elem = std::begin(container); elem != std::end(container); ++elem)



//
//