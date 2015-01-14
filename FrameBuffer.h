#pragma once

#include "FEngine.h"

class FrameBuffer
{
public:
	FrameBuffer(std::string name, int width, int height);
	~FrameBuffer();

	//Creates a new texture and link it to the buffer
	void addTexture(std::string textureName, GLint format);
	//Bind the buffer to write into the textures
	void bindForDrawingToTextures();
	//Bind the buffer textures
	void bindTextures(int idStart = 0); //Idstart is the start of the active texture (i.e if u bind several buffers at the same time this prevents the textures to use the same location)
	//Unbind the framebuffer
	void unBind();

	//Return the texture by the name, is the same as calling it from the resourceManager
	Texture* getFrameBufferTexture(std::string textureName);

protected:
	//OPENGL id of the the frame buffer
	GLuint mFrameBufferId;
	//Identification name of the frame buffer
	std::string mName;
	//Size of the frame buffer, all the textures has this size
	int mWidth, mHeight;

	//Map holding all the framebuffer texture pointers
	std::unordered_map<std::string, Texture*> mTextureMap;
};

