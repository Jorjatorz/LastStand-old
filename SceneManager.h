#pragma once

#include "FEngine.h"

class SceneManager
{
public:
	SceneManager();
	~SceneManager();

	//Add all the movable objects of all the nodes into the rendering queueu
	void processRootSceneNode();

	//Returns a pointer to the root scenenode
	SceneNode* getRootSceneNode();
	//Inserts the node to the map (so we have easy acces to it and fast)
	void addSceneNodeToScene(SceneNode* node);
	//Return a scenenode
	SceneNode* getSceneNode(std::string name);

	//Creates a new entity
	Entity* createEntity(std::string entityName, std::string meshName);
	//Deletes a entity
	void deleteEntity(std::string entityName);
	//Return a entity already created
	Entity* getEntity(std::string entityName);

private:
	//Root scenenode for the whoel scene. Created in the constructor
	SceneNode* mRootSceneNode;

	//Map containing all the Scenenodes
	std::unordered_map<std::string, SceneNode*> mSceneNodeMap;
	//Map containing all the entities
	std::unordered_map<std::string, Entity*> mEntityMap;
};

