#pragma once

#include "FEngine.h"

class Renderer
{
public:
	Renderer();
	~Renderer();

	void processOpaqueRenderingQueue();

private:
	//Queue of the entities to be rendered
	std::queue<Entity*> mOpaqueRenderQueue;
};

