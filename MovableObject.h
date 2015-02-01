#pragma once

#include "FEngine.h"

//Abstrac class defining an object that can be attached to a scene node

class MovableObject
{
public:
	MovableObject();
	~MovableObject();

	std::string getName()
	{
		return mName;
	}
	bool isAttached()
	{
		return mAttachedToSceneNode;
	}
	void setAttached(bool b)
	{
		mAttachedToSceneNode = b;
	}

private:
	//MovableObject name
	std::string mName;
	//True if attached to a scenenode
	bool mAttachedToSceneNode;
};

