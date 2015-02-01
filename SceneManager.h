#pragma once

#include "FEngine.h"

class SceneManager
{
public:
	SceneManager();
	~SceneManager();

	//Returns a pointer to the root scenenode
	SceneNode* getRootSceneNode();

private:
	//Root scenenode for the whoel scene. Created in the constructor
	SceneNode* mRootSceneNode;
};

