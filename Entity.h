#pragma once

#include "FEngine.h"

#include "MovableObject.h"

//Movable object that has a MESH (e.g. Group of vertex loaded from a file that forms a shape)

class Entity: public MovableObject
{
public:
	Entity();
	~Entity();

	//Renders the entity into the buffer
	void drawToBuffer();

private:
	//if true the entity will be rendered into the buffer
	bool mVisible;
};

