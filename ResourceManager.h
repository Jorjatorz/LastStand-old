#pragma once

#include "FEngine.h"
#include "Singleton.h"

//Class that handles all the resource components of the engine, such as shadrs, textures ,meshes, etc

class ResourceManager: public Singleton<ResourceManager>
{
public:
	ResourceManager();
	~ResourceManager();

	//Load a new shader into the memory
	Shader* loadShaderIntoMemory(std::string shaderName);
	//Delete the shader stored in memory
	void deleteShaderFromMemory(std::string shaderName);
	//Return the shader stored in memory
	Shader* getShaderInMemory(std::string shaderName);

	//Load a new Texture into the memory
	Texture* loadTextureIntoMemoryFromFile(std::string textureName);
	//Creates a new Texture and store it in the memory
	Texture* createNewTextureInMemory(std::string textureName, unsigned int width, unsigned int height, GLint format, bool mipmap);
	//Delete the texture stored in memory
	void deleteTextureFromMemory(std::string textureName);
	//Return the texture stored in memory
	Texture* getTextureInMemory(std::string textureName);

private:
	//Map containing all the shaders loaded
	std::unordered_map<std::string, Shader*> mShaderMap;
	//Map containing all the texture loaded
	std::unordered_map<std::string, Texture*> mTextureMap;
};

