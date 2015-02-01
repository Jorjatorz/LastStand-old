#include "SceneManager.h"

#include "SceneNode.h"

SceneManager::SceneManager()
{
	//Allocate the scenenode root
	mRootSceneNode = new SceneNode("RootNode");
}


SceneManager::~SceneManager()
{
	delete mRootSceneNode;
}

SceneNode* SceneManager::getRootSceneNode()
{
	return mRootSceneNode;
}