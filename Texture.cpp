#include "Texture.h"


Texture::Texture()
	:mWidth(0),
	mHeight(0),
	mFormat(-1),
	mTextureID(-1),
	isMipmap(false)
{
}


Texture::~Texture()
{
	//Delete the opengl texture
	glDeleteTextures(1, &mTextureID);
}

bool Texture::loadTexture(std::string texturePath, bool mipmap, GLint format)
{
	//FROM FREEIMAGE EXAMPLE
	//image format
	FREE_IMAGE_FORMAT fif = FIF_UNKNOWN;
	//pointer to the image, once loaded
	FIBITMAP *dib(0);
	//pointer to the image data
	BYTE* bits(0);
	//image width and height
	unsigned int width(0), height(0);

	//check the file signature and deduce its format
	fif = FreeImage_GetFileType(texturePath.c_str(), 0);
	//if still unknown, try to guess the file format from the file extension
	if (fif == FIF_UNKNOWN)
	{
		fif = FreeImage_GetFIFFromFilename(texturePath.c_str());
	}
	//if still unkown, return failure
	if (fif == FIF_UNKNOWN)
	{
		FE_LOG(FE_LOG::ERR, "Unknown format of texture, can't load it: " + texturePath);
		return false;
	}

	//check that the plugin has reading capabilities and load the file
	if (FreeImage_FIFSupportsReading(fif))
	{
		dib = FreeImage_Load(fif, texturePath.c_str());

		FREE_IMAGE_COLOR_TYPE type = FreeImage_GetColorType(dib);
		//If it has no 32 bit color format convert to it
		if (FREE_IMAGE_COLOR_TYPE::FIC_RGBALPHA != type)
		{
			dib = FreeImage_ConvertTo32Bits(dib);
		}
	}
	//if the image failed to load, return failure
	if (!dib)
	{
		FE_LOG(FE_LOG::ERR, "Texture format not supported: " + texturePath);
		return false;
	}

	//retrieve the image data
	bits = FreeImage_GetBits(dib);
	//get the image width and height
	width = FreeImage_GetWidth(dib);
	height = FreeImage_GetHeight(dib);
	//if this somehow one of these failed (they shouldn't), return failure
	if ((bits == 0) || (width == 0) || (height == 0))
	{
		FE_LOG(FE_LOG::ERR, "Error getting bits, width or height of texture: " + texturePath);
		return false;
	}

	//If the texture hasnt being already created create a new one, else update it
	if (mTextureID = -1)
	{
		generateTexture(width, height, format, mipmap, bits);
	}
	else
	{
		updateTexture(width, height, format, mipmap, bits);
	}

	//Free FreeImage's copy of the data
	FreeImage_Unload(dib);

	return true;

}

void Texture::generateTexture(unsigned int width, unsigned int height, GLint format, bool mipmap, const GLvoid* pixels)
{
	//Create the texture
	GLuint tex;
	glGenTextures(1, &tex);

	glBindTexture(GL_TEXTURE_2D, tex);
	glTexImage2D(GL_TEXTURE_2D, 0, format, width, height, 0, GL_BGRA, GL_UNSIGNED_BYTE, pixels); //Free image loads in BGR

	if (mipmap)
	{
		glGenerateMipmap(GL_TEXTURE_2D);

		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);

		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR_MIPMAP_LINEAR);

		isMipmap = true;
	}
	else
	{
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);

		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);

		isMipmap = false;
	}

	mFormat = format;
	mWidth = width;
	mHeight = height;

	mTextureID = tex;
}

void Texture::updateTexture(int width, int height, GLint format, bool mipmap, const GLvoid* pixels)
{
	//Just modify the texture information
	glBindTexture(GL_TEXTURE_2D, mTextureID);
	glTexImage2D(GL_TEXTURE_2D, 0, format, width, height, 0, GL_BGRA, GL_UNSIGNED_BYTE, pixels); //Free iamge loads in BGR
	glBindTexture(GL_TEXTURE_2D, 0);
}

GLuint Texture::getTextureId()
{
	return mTextureID;
}