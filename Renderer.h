#pragma once

#include "FEngine.h"

#include "Singleton.h"

class Renderer: public Singleton<Renderer>
{
public:
	Renderer();
	~Renderer();

	//Process all the objects in the opaque queue
	void processOpaqueRenderingQueue(const Matrix4& PVMatrix);
	//Push a new object into the opaquequeue
	void pushObjectToOpaqueQueue(MovableObject* obj);
	//Clear the opaquequeue
	void clearOpaqueQueue();

private:
	//Queue of the entities to be rendered
	std::deque<MovableObject*> mOpaqueRenderQueue;
};

