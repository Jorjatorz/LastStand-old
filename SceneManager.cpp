#include "SceneManager.h"

#include "Entity.h"
#include "Renderer.h"
#include "SceneNode.h"

SceneManager::SceneManager()
{
	//Allocate the scenenode root
	mRootSceneNode = new SceneNode("RootNode", this);
}


SceneManager::~SceneManager()
{
	//Delete all the nodes
	delete mRootSceneNode;
	mSceneNodeMap.clear();

	//Delete all entities (after deleting nodes as nodes detach objects when deleting them)
	foreach(entity, mEntityMap)
	{
		delete entity->second;
	}
	mEntityMap.clear();
}

SceneNode* SceneManager::getRootSceneNode()
{
	return mRootSceneNode;
}

Entity* SceneManager::createEntity(std::string entityName, std::string meshName)
{
	if (mEntityMap.find(entityName) != mEntityMap.end())
	{
		FE_LOG(FE_LOG::ERR, "Entity already exists, can't create it: " + entityName);
		assert(0);
	}

	Entity* newEnt = new Entity(entityName, meshName);

	mEntityMap.emplace(std::make_pair(entityName, newEnt));

	return newEnt;
}

void SceneManager::deleteEntity(std::string entityName)
{
	auto it = mEntityMap.find(entityName);
	if (it == mEntityMap.end())
	{
		FE_LOG(FE_LOG::ERR, "Can't delete the entity, it doesn't exist: " + entityName);
		assert(0);
	}

	delete it->second;
	mEntityMap.erase(it);
}

Entity* SceneManager::getEntity(std::string entityName)
{
	auto it = mEntityMap.find(entityName);
	if (it == mEntityMap.end())
	{
		FE_LOG(FE_LOG::ERR, "Can't return the entity, it doesn't exist: " + entityName);
		assert(0);
	}

	return it->second;
}

void SceneManager::processRootSceneNode()
{
	//Get the renderer singleton and clear the renderer queue
	Renderer* mRenderer = Renderer::getSingleton();
	mRenderer->clearOpaqueQueue();

	//BFS traversal
	std::queue<SceneNode*> toTraverseQueue;
	toTraverseQueue.push(mRootSceneNode);

	while (!toTraverseQueue.empty())
	{
		//Get the first node in list
		SceneNode* node = toTraverseQueue.front();
		toTraverseQueue.pop();

		foreach(object, node->getMovablesObjectsMap())
		{
			//Only add renderable items
			if (object->second->getType() == MovableObject::RENDERABLE)
			{
				if (object->second->isVisible())
				{
					mRenderer->pushObjectToOpaqueQueue(object->second);
				}
			}
		}

		foreach(child, node->getChildNodesMap())
		{
			toTraverseQueue.push(child->second);
		}
	}
}

void SceneManager::addSceneNodeToScene(SceneNode* node)
{
	mSceneNodeMap.emplace(std::make_pair(node->getName(), node));
}

SceneNode* SceneManager::getSceneNode(std::string name)
{
	auto it = mSceneNodeMap.find(name);
	if (it == mSceneNodeMap.end())
	{
		FE_LOG(FE_LOG::ERR, "Can't find that scenenode, it doesn't exists: " + name);
		assert(0);
	}

	return it->second;
}