#include "MovableObject.h"


MovableObject::MovableObject(std::string name, tTypeEnum type)
	:mName(name),
	mType(type),
	mVisible(true),
	mParentSceneNode(NULL)
{
}


MovableObject::~MovableObject()
{
}

void MovableObject::attachToNode(SceneNode* node)
{
	mParentSceneNode = node;
}