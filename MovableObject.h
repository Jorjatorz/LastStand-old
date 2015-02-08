#pragma once

#include "FEngine.h"

//Abstrac class defining an object that can be attached to a scene node

class MovableObject
{
public:

	typedef enum
	{
		RENDERABLE //ProcessMovable -> renders the object (bind the opengl buffers)
	}tTypeEnum;

	MovableObject(std::string name, tTypeEnum type);
	~MovableObject();

	//Depending on each movable object it will do a different kind of thing
	virtual void rendersMovableObject(const Matrix4& PVMatrix) = 0;

	std::string getName()
	{
		return mName;
	}

	tTypeEnum getType()
	{
		return mType;
	}

	void attachToNode(SceneNode* node);
	bool isAttached()
	{
		return mAttachedSceneNode != NULL;
	}

	//True if the object is visible
	bool isVisible()
	{
		return mVisible;
	}

protected:
	//MovableObject name
	std::string mName;
	//True if attached to a scenenode
	SceneNode* mAttachedSceneNode;
private:
	//MovableObject type
	tTypeEnum mType;
	//if true the object is visible
	bool mVisible;
};

