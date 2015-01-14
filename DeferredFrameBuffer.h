#pragma once

#include "FEngine.h"
#include "FrameBuffer.h"

//FrameBuffer that stores  Color and normal textures and depth texture

class DeferredFrameBuffer: public FrameBuffer
{
public:
	DeferredFrameBuffer(std::string name, int width, int height);
	~DeferredFrameBuffer();

private:
	//Depth texture id
	GLuint depthTextureId;
};

