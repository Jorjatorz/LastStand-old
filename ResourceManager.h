#pragma once

#include "FEngine.h"
#include "Singleton.h"

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

private:
	//Map containing all the shaders loaded
	std::unordered_map<std::string, Shader*> mShaderMap;
};

