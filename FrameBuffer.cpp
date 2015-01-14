#include "FrameBuffer.h"

#include "Shader.h"
#include "ResourceManager.h"
#include "Texture.h"

FrameBuffer::FrameBuffer(std::string name, int width, int height)
{
	mName = name;
	mWidth = width;
	mHeight = height;

	//Create the framebuffer in the constructor
	glGenFramebuffers(1, &mFrameBufferId);
}

FrameBuffer::~FrameBuffer()
{
	glDeleteFramebuffers(1, &mFrameBufferId);
}

void FrameBuffer::addTexture(std::string textureName, GLint format)
{
	//Create the new texture, by deafult no mipmap
	Texture* texture = ResourceManager::getSingleton()->createNewTextureInMemory(textureName, mWidth, mHeight, format, false);
	mTextureMap.emplace(textureName, texture);

	glBindFramebuffer(GL_FRAMEBUFFER, mFrameBufferId);
	glFramebufferTexture2D(GL_FRAMEBUFFER, GL_COLOR_ATTACHMENT0 + mTextureMap.size() - 1, GL_TEXTURE_2D, texture->getTextureId(), 0); //mTextureMap.size() - 1 Because we want to start at 0
}

void FrameBuffer::bindForDrawingToTextures()
{
	glBindFramebuffer(GL_FRAMEBUFFER, mFrameBufferId);
	//Create a vector for storing the buffer color attachments, reserve space for all the textures attached to the buffer
	std::vector<GLuint> bufferAttachments;
	bufferAttachments.reserve(mTextureMap.size());
	
	for (size_t i = 0; i <= mTextureMap.size(); ++i)
	{
		bufferAttachments.push_back(GL_COLOR_ATTACHMENT0 + i);
	}
	//Set the buffer to draw
	glDrawBuffers(mTextureMap.size(), bufferAttachments.data());
}

void FrameBuffer::bindTextures(int idStart)
{
	//Detach any binded frame buffer
	glBindFramebuffer(GL_FRAMEBUFFER, 0);

	int i = 0;
	foreach(texture, mTextureMap)
	{
		glActiveTexture(GL_TEXTURE0 + i + idStart);
		glBindTexture(GL_TEXTURE_2D, texture->second->getTextureId());
		i++;
	}
}

void FrameBuffer::unBind()
{
	glBindFramebuffer(GL_FRAMEBUFFER, 0);
}

Texture* FrameBuffer::getFrameBufferTexture(std::string textureName)
{
	return mTextureMap.find(textureName)->second;
}