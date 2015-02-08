#include "MovableObject.h"


MovableObject::MovableObject(std::string name, tTypeEnum type)
	:mName(name),
	mType(type),
	mVisible(true),
	mAttachedSceneNode(NULL)
{
}


MovableObject::~MovableObject()
{
}

void MovableObject::attachToNode(SceneNode* node)
{
	mAttachedSceneNode = node;
}