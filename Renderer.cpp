#include "Renderer.h"

#include "Entity.h"

Renderer::Renderer()
{
}


Renderer::~Renderer()
{
}

void Renderer::processOpaqueRenderingQueue()
{
	while (!mOpaqueRenderQueue.empty())
	{
		mOpaqueRenderQueue.front()->drawToBuffer();
		mOpaqueRenderQueue.pop();
	}
}