#include "ResourceManager.h"

#include "Shader.h"
#include "Texture.h"

ResourceManager::ResourceManager()
{
}


ResourceManager::~ResourceManager()
{
	//Delete all shaders
	foreach(shader, mShaderMap)
	{
		delete shader->second;
	}
	mShaderMap.clear();
	//Delete all textures
	foreach(texture, mTextureMap)
	{
		delete texture->second;
	}
	mTextureMap.clear();
}

Shader* ResourceManager::loadShaderIntoMemory(std::string shaderName)
{
	FE_LOG(FE_LOG::INFO, "Loading Shader " + shaderName);

	//Create a new shader with a name(to identify it in the log)
	Shader* newShader = new Shader(shaderName);
	//Load the shader from a file
	if (newShader->loadShader("Data\\Shaders\\" + shaderName))
	{
		FE_LOG(FE_LOG::INFO, shaderName + " shader loaded.");
		mShaderMap.emplace(std::make_pair(shaderName, newShader));
	}
	else
	{
		FE_LOG(FE_LOG::ERR, "Couldn't load Shader: Data\\Shaders\\" + shaderName);
		delete newShader;
	}

	return newShader;
	
}
void ResourceManager::deleteShaderFromMemory(std::string shaderName)
{
	delete mShaderMap.find(shaderName)->second;
}
Shader* ResourceManager::getShaderInMemory(std::string shaderName)
{
	return mShaderMap.find(shaderName)->second;
}

Texture* ResourceManager::loadTextureIntoMemoryFromFile(std::string textureName)
{
	FE_LOG(FE_LOG::INFO, "Loading Texture " + textureName);

	Texture* newTexture = new Texture();
	//Load the texture from a file, by default with mipmap and RGBA format
	if (newTexture->loadTexture("Data\\Textures\\" + textureName, true, GL_RGBA))
	{
		FE_LOG(FE_LOG::INFO, textureName + " texture loaded.");
		mTextureMap.emplace(std::make_pair(textureName, newTexture));
	}
	else
	{
		FE_LOG(FE_LOG::ERR, "Couldn't load texture: Data\\Textures\\" + textureName);
		delete newTexture;
	}

	return newTexture;
}

Texture* ResourceManager::createNewTextureInMemory(std::string textureName, unsigned int width, unsigned int height, GLint format, bool mipmap)
{
	Texture* newTexture = new Texture();
	//Generate the new texture without pixels
	newTexture->generateTexture(width, height, format, mipmap, NULL);

	FE_LOG(FE_LOG::INFO, "Texture Created: " + textureName);

	return newTexture;
}

void ResourceManager::deleteTextureFromMemory(std::string textureName)
{
	delete mTextureMap.find(textureName)->second;
}

Texture* ResourceManager::getTextureInMemory(std::string textureName)
{
	return mTextureMap.find(textureName)->second;
}