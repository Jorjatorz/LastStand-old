#include "ResourceManager.h"

#include "Mesh.h"
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
	//Delete all mshes
	foreach(mesh, mMeshMap)
	{
		delete mesh->second;
	}
	mMeshMap.clear();
}

Shader* ResourceManager::loadShaderIntoMemoryFromFile(std::string shaderName)
{
	FE_LOG(FE_LOG::INFO, "Loading Shader " + shaderName);

	auto it = mShaderMap.find(shaderName);
	if (it != mShaderMap.end())
	{
		FE_LOG(FE_LOG::ERR, "Can't load the shader into memory, it already exist: " + shaderName);
		assert(0);
	}

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
	auto it = mShaderMap.find(shaderName);
	if (it == mShaderMap.end())
	{
		FE_LOG(FE_LOG::ERR, "Can't delete the shader from memory, it doesnt exist: " + shaderName);
		assert(0);
	}

	delete it->second;
	mShaderMap.erase(it);
}
Shader* ResourceManager::getShaderInMemory(std::string shaderName)
{
	auto it = mShaderMap.find(shaderName);
	if (it == mShaderMap.end())
	{
		FE_LOG(FE_LOG::ERR, "Can't return the shader in memory, it doesnt exist: " + shaderName);
		assert(0);
	}

	return it->second;
}

Texture* ResourceManager::loadTextureIntoMemoryFromFile(std::string textureName)
{
	FE_LOG(FE_LOG::INFO, "Loading Texture " + textureName);

	auto it = mTextureMap.find(textureName);
	if (it != mTextureMap.end())
	{
		FE_LOG(FE_LOG::ERR, "Can't load the texture into memory, it already exists: " + textureName);
		assert(0);
	}

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
	auto it = mTextureMap.find(textureName);
	if (it != mTextureMap.end())
	{
		FE_LOG(FE_LOG::ERR, "Can't create the texture into memory, it already exists: " + textureName);
		assert(0);
	}

	Texture* newTexture = new Texture();
	//Generate the new texture without pixels
	newTexture->generateTexture(width, height, format, mipmap, NULL);

	FE_LOG(FE_LOG::INFO, "Texture Created: " + textureName);

	return newTexture;
}

void ResourceManager::deleteTextureFromMemory(std::string textureName)
{
	auto it = mTextureMap.find(textureName);
	if (it == mTextureMap.end())
	{
		FE_LOG(FE_LOG::ERR, "Can't delete the texture from memory, it doesnt exist: " + textureName);
		assert(0);
	}

	delete it->second;
	mTextureMap.erase(it);
}

Texture* ResourceManager::getTextureInMemory(std::string textureName)
{
	auto it = mTextureMap.find(textureName);
	if (it == mTextureMap.end())
	{
		FE_LOG(FE_LOG::ERR, "Can't return the texture into memory, it doesnt exist: " + textureName);
		assert(0);
	}

	return it->second;
}

//Load a mesht into the memory
Mesh* ResourceManager::loadMeshIntoMemory(std::string meshName)
{
	FE_LOG(FE_LOG::INFO, "Loading Mesh " + meshName);

	auto it = mMeshMap.find(meshName);
	if (it != mMeshMap.end())
	{
		//We return the mesh, dont pop an error
		/*FE_LOG(FE_LOG::ERR, "Mesh already into memory, can't load it " + meshName);
		assert(0);*/

		return it->second;
	}

	Mesh* newMesh = new Mesh(meshName);
	//Load the mesh from a file
	if (newMesh->loadMesh("Data\\Meshes\\" + meshName))
	{
		FE_LOG(FE_LOG::INFO, meshName + " mesh loaded.");
		mMeshMap.emplace(std::make_pair(meshName, newMesh));
	}
	else
	{
		FE_LOG(FE_LOG::ERR, "Couldn't load mesh: Data\\Meshes\\" + meshName);
		delete newMesh;
	}

	return newMesh;
}
//Delete a mesh from memory
void ResourceManager::deleteMeshFromMemory(std::string meshName)
{
	auto it = mMeshMap.find(meshName);
	if (it == mMeshMap.end())
	{
		FE_LOG(FE_LOG::ERR, "Can't delete the mesh from memory, it doesnt exist: " + meshName);
		assert(0);
	}

	delete it->second;
	mMeshMap.erase(it);
}
//Return the mesh stored in meory
Mesh* ResourceManager::getMeshInMemory(std::string meshName)
{
	auto it = mMeshMap.find(meshName);
	if (it == mMeshMap.end())
	{
		FE_LOG(FE_LOG::ERR, "Can't return the mesh in memory, it doesnt exist: " + meshName);
		assert(0);
	}

	return it->second;
}