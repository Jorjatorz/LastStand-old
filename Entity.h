#pragma once

#include "FEngine.h"

#include "MovableObject.h"

//Movable object that has a MESH (e.g. Group of vertex loaded from a file that forms a shape)

class Entity: public MovableObject
{
public:
	Entity(std::string name, std::string meshName);
	~Entity();

	//Renders the entity into the buffer
	void rendersMovableObject(const Matrix4& PVMatrix);

	//Attach a mesh to the entity
	void attachNewMesh(std::string meshName);

private:
	//Mesh attached to the entity
	Mesh* mAttachedMesh;
};

