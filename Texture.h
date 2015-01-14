#pragma once

#include "FEngine.h"

//FreeImage for importing textures
#include "FreeImage.h"

class Texture
{
public:
	Texture(void);
	~Texture(void);

	//Load a texture from a file, false if an error ocurred
	bool loadTexture(std::string texturePath, bool mipmap, GLint format);
	//Generate a texture into memory. (Not loaded from file)
	void generateTexture(unsigned int width, unsigned int height, GLint format, bool mipmap, const GLvoid* pixels);
	//Update the current texture to have the new parameters
	void updateTexture(int width, int height, GLint format, bool mipmap, const GLvoid* pixels);

	//Return the texture opengl id
	GLuint getTextureId();

private:
	//is mipmap
	bool isMipmap;
	//Texture format
	GLint mFormat;
	//Texture dimensions
	unsigned int mWidth, mHeight;
	//texture ID
	GLuint mTextureID;


};
