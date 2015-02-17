#include "Entity.h"

#include "Mesh.h"
#include "ResourceManager.h"
#include "SceneNode.h"
#include "Shader.h"

Entity::Entity(std::string name, std::string meshName)
	:MovableObject(name, MovableObject::RENDERABLE)
{
	attachNewMesh(meshName);
}


Entity::~Entity()
{
}

void Entity::rendersMovableObject(const Matrix4& PVMatrix)
{
	//Bind material shader...
	Shader* renderShader = ResourceManager::getSingleton()->getShaderInMemory("basicObject");
	renderShader->bind();

	renderShader->uniformMatrix("MVP", PVMatrix * mParentSceneNode->getSceneNodeMatrix());
	renderShader->uniformMatrix("NormalM", mParentSceneNode->getSceneNodeMatrix().getInverseMatrix().getTransposeMatrix());

	//Render the mesh
	mAttachedMesh->renderAllSubMeshes();

	Shader::unBind();
}

void Entity::attachNewMesh(std::string meshName)
{
	//Load the mesh, in a future this can be added to a queue instead of loading the mesh when creating the entity
	mAttachedMesh = ResourceManager::getSingleton()->loadMeshIntoMemory(meshName);
}