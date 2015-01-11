#include "ResourceManager.h"

#include "Shader.h"

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
}

Shader* ResourceManager::loadShaderIntoMemory(std::string shaderName)
{
	Shader* newShader = new Shader("Data\\Shaders\\" + shaderName);
	mShaderMap.emplace(std::make_pair(shaderName, newShader));

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