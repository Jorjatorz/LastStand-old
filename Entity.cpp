#include "Entity.h"

#include "Mesh.h"
#include "ResourceManager.h"
#include "SceneNode.h"
#include "Shader.h"

Entity::Entity(std::string name, std::string meshName)
	:MovableObject(name, MovableObject::RENDERABLE)
{
	//Load the mesh, in a future this can be added to a queue instead of loading the mesh when creating the entity
	mAttachedMesh = ResourceManager::getSingleton()->loadMeshIntoMemory(meshName);
}


Entity::~Entity()
{
}

void Entity::rendersMovableObject(const Matrix4& PVMatrix)
{
	//Bind material shader...
	ResourceManager::getSingleton()->getShaderInMemory("basicObject")->bind();
	ResourceManager::getSingleton()->getShaderInMemory("basicObject")->uniformMatrix("MVP", PVMatrix * mAttachedSceneNode->getSceneNodeMatrix());

	//Render the mesh
	mAttachedMesh->renderAllSubMeshes();

	Shader::unBind();
}