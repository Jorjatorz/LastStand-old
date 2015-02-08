#include "Renderer.h"

#include "MovableObject.h"

Renderer::Renderer()
{
}


Renderer::~Renderer()
{
}

void Renderer::processOpaqueRenderingQueue(const Matrix4& PVMatrix)
{
	while (!mOpaqueRenderQueue.empty())
	{
		mOpaqueRenderQueue.front()->rendersMovableObject(PVMatrix);
		mOpaqueRenderQueue.pop_front();
	}
}

void Renderer::pushObjectToOpaqueQueue(MovableObject* obj)
{
	mOpaqueRenderQueue.push_back(obj);
}

void Renderer::clearOpaqueQueue()
{
	mOpaqueRenderQueue.clear();
}