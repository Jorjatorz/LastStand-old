#include "DeferredFrameBuffer.h"


DeferredFrameBuffer::DeferredFrameBuffer(std::string name, int width, int height)
	:FrameBuffer(name, width, height)
{
	//Create the textures
	//Color
	addTexture("DeferredFrameBufferText_Color", GL_RGBA8);
	//Normal
	addTexture("DeferredFrameBufferText_Normal", GL_RGBA8);

	//Create the Depth texture
	glGenTextures(1, &depthTextureId);
	glBindTexture(GL_TEXTURE_2D, depthTextureId);

	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);

	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);


	glTexImage2D(GL_TEXTURE_2D, 0, GL_DEPTH_COMPONENT24, mWidth, mHeight, 0, GL_DEPTH_COMPONENT, GL_FLOAT, 0);

	glBindFramebuffer(GL_FRAMEBUFFER, mFrameBufferId);
	glFramebufferTexture2D(GL_FRAMEBUFFER, GL_DEPTH_ATTACHMENT, GL_TEXTURE_2D, depthTextureId, 0);

	glBindTexture(GL_TEXTURE_2D, 0);
}


DeferredFrameBuffer::~DeferredFrameBuffer()
{
	glDeleteTextures(1, &depthTextureId);
}
