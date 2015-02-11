#include "SceneNode.h"

#include "Root.h"
#include "MovableObject.h"
#include "SceneManager.h"

SceneNode::SceneNode(std::string sceneNodeName, SceneManager* manager, SceneNode* nodeParent)
	:mName(sceneNodeName),
	mParent(nodeParent),
	mPosition(0.0),
	mOrientation(),
	mScale(1.0),
	mDerivedPosition(0.0),
	mDerivedOrientation(0.0),
	mDerivedScale(1.0),
	mSceneNodeMatrix(1.0),
	mDirty(true),
	creator(manager)
{
	updateFromParent();
}

SceneNode::~SceneNode(void)
{
	//delete all childs
	deleteAllChilds();
	//detach all objects
	detachAllObjects();
}

void SceneNode::setParentSceneNode(SceneNode* newParent)
{
	//Change the parent scenenode, thus we have to calcualte the derived transforms again
	mParent = newParent;
	mDirty = true;
}

SceneNode* SceneNode::createChildSceneNode(std::string name)
{
	//Check if that node already exists, if true return it
	auto it = mChildNodesMap.find(name);
	if (it != mChildNodesMap.end())
	{
		FE_LOG(FE_LOG::ERR, "Child node already exists, cant create it: " + name);
		assert(0);
	}

	//else create a new one
	SceneNode* newSceneNode = new SceneNode(name, creator, this);
	creator->addSceneNodeToScene(newSceneNode);

	mChildNodesMap.insert(std::make_pair(name, newSceneNode));

	return newSceneNode;
}

SceneNode* SceneNode::createChildSceneNode(std::string name, SceneNode* newChild)
{
	//Check if that node already exists, if true return it
	auto it = mChildNodesMap.find(name);
	if (it != mChildNodesMap.end())
	{
		FE_LOG(FE_LOG::ERR, "Child node already exists, cant create it: " + name);
		assert(0);
	}

	//else insert it
	mChildNodesMap.insert(std::make_pair(name, newChild));
	creator->addSceneNodeToScene(newChild);

	return newChild;
}

SceneNode* SceneNode::createChildSceneNode(std::string name, Vector3 initialPosition)
{
	//Check if that node already exists, if true return it
	auto it = mChildNodesMap.find(name);
	if (it != mChildNodesMap.end())
	{
		FE_LOG(FE_LOG::ERR, "Child node already exists, cant create it: " + name);
		assert(0);
	}

	//else create a new one
	SceneNode* newSceneNode = new SceneNode(name, creator, this);
	creator->addSceneNodeToScene(newSceneNode);

	newSceneNode->setPosition(initialPosition);

	mChildNodesMap.insert(std::make_pair(name, newSceneNode));

	return newSceneNode;
}

void SceneNode::deleteChildrenNode(std::string childName)
{
	//Check if that node already exists, if true delete it
	auto it = mChildNodesMap.find(childName);
	if (it != mChildNodesMap.end())
	{
		delete it->second;
		mChildNodesMap.erase(it);

		return;
	}

	FE_LOG(FE_LOG::ERR, "Child node doesnt exists, cant delete it: " + childName);
	assert(0);
}
void SceneNode::deleteChildrenNode(SceneNode* child)
{
	deleteChildrenNode(child->getName());
}
void SceneNode::deleteAllChilds()
{
	foreach(child, mChildNodesMap)
	{
		delete child->second;
	}
	mChildNodesMap.clear();
}

void SceneNode::attachObject(MovableObject* mNewObject)
{
	//If its already attached crash the program
	if (mNewObject->isAttached())
	{
		FE_LOG(FE_LOG::ERR, "Object already attached to other SceneNode: " + mNewObject->getName());
		assert(0);
	}

	mMovableObjectsMap.insert(std::make_pair(mNewObject->getName(), mNewObject));
	mNewObject->attachToNode(this);
}

void SceneNode::detachObject(std::string objName)
{
	auto it = mMovableObjectsMap.find(objName);
	if (it != mMovableObjectsMap.end())
	{
		it->second->attachToNode(NULL);
		mMovableObjectsMap.erase(it);

		return;
	}

	FE_LOG(FE_LOG::ERR, "Object doesnt exists, cant detach it from node: " + objName);
	assert(0);
}

void SceneNode::detachObject(MovableObject* movableObject)
{
	detachObject(movableObject->getName());
}

void SceneNode::detachAllObjects()
{
	foreach(obj, mMovableObjectsMap)
	{
		obj->second->attachToNode(NULL);
	}
	mMovableObjectsMap.clear();
}

void SceneNode::updateFromParent()
{
	processDerivedPosition();
	processDerivedOrientation();
	processDerivedScale();

	//if the node position has changed or the derived positon (thus the parent) has changed modify the sceneNodeMatrix
	if (mDirty || mParent->mDirty)
	{
		mSceneNodeMatrix = Matrix4(1.0);

		updateChildrens();
		//update matrix
		mSceneNodeMatrix.translate(mDerivedPosition);
		mSceneNodeMatrix = mSceneNodeMatrix * mDerivedOrientation.toMat4();
		mSceneNodeMatrix.scale(mDerivedScale);
	}

	mDirty = false;

}

void SceneNode::updateChildrens()
{
	foreach(child, mChildNodesMap)
	{
		child->second->updateFromParent();
	}
}

void SceneNode::processDerivedPosition()
{
	//if we have parent
	if (mParent != NULL)
	{
		mDerivedPosition = mParent->mDerivedPosition + mPosition;
	}
	else
	{
		mDerivedPosition = mPosition;
	}
}
void SceneNode::processDerivedOrientation()
{
	//if we have parent
	if (mParent != NULL)
	{
		mDerivedOrientation = mParent->mDerivedOrientation * mOrientation;
	}
	else
	{
		mDerivedOrientation = mOrientation;
	}
}
void SceneNode::processDerivedScale()
{
	//if we have parent
	if (mParent != NULL)
	{
		mDerivedScale = mParent->mDerivedScale * mScale;
	}
	else
	{
		mDerivedScale = mScale;
	}
}


void SceneNode::translate(Vector3 trans)
{
	mPosition += trans * Root::getSingleton()->getLastFrameDelayInSeconds();// *mSceneManager->mDeltaTime;

	mDirty = true;

	//Position has changed so we update all
	updateFromParent();
}

void SceneNode::rotate(Vector3 axis, float angle)
{
	/*Quaternion q;
	q = glm::angleAxis(angle, axis); //Suppose angle is in degrees
	glm::normalize(q); //Normalize to avoid drift

	mOrientation = q; //Order is */

	Matrix4 rotationM;
	if (axis != Vector3(0.0)) //Just in case
	{
		rotationM.rotate(angle * Root::getSingleton()->getLastFrameDelayInSeconds(), axis);
	}

	//Create a quaternion from the matrix
	mOrientation = mOrientation * Quaternion(rotationM);

	mDirty = true;

	//Rotation has changed so we update all
	updateFromParent();
}

void SceneNode::scale(Vector3 axis)
{
	mScale += axis * Root::getSingleton()->getLastFrameDelayInSeconds();

	mDirty = true;

	//Scale has changed so we update all
	updateFromParent();
}

void SceneNode::lookAt(Vector3 lookAtPoint, Vector3 objectFacing)
{
	/* From internet (not works)
	Vector3 lookVector = lookAtPoint;
	assert(lookVector != mPosition);

	Vector3 direction = glm::normalize(lookVector - mPosition);
	float dot = glm::dot(Vector3(0.0, 0.0, 1.0), direction);

	Quaternion rotation;
	if (fabs(dot - (-1.0f)) < 0.000001f) {
	rotation = glm::angleAxis((float)glm::degrees(M_PI), Vector3(0.0, 1.0, 0.0));
	mOrientation = rotation;
	return;
	}
	else if (fabs(dot - (1.0f)) < 0.000001f) {
	rotation = Quaternion();
	mOrientation = rotation;
	return;
	}

	float angle = glm::degrees(acosf(dot));

	Vector3 cross = glm::normalize(glm::cross(Vector3(0.0, 0.0, 1.0), direction));
	rotation = glm::normalize(glm::angleAxis(angle, cross));

	mOrientation = mOrientation * rotation;*/

	
	
	
	/* Mine, works
	Vector3 targetVec = glm::normalize(lookAtPoint - mPosition);
	Vector3 mDir = objectFacing;
	Vector3 mAxis = glm::cross(targetVec, mDir);
	float angle = glm::acos(glm::dot(targetVec, mDir));

	if (mAxis != Vector3(0.0))
	{
		rotate(mAxis, -glm::degrees(angle));
	}*/

}
void SceneNode::setPosition(Vector3 newPos)
{
	mPosition = newPos;

	mDirty = true;

	//Position changed, update
	updateFromParent();
}
void SceneNode::setOrientation(Quaternion newOrientation)
{
	mOrientation = newOrientation;

	mDirty = true;

	//Orientation changed, update
	updateFromParent();
}
void SceneNode::setScale(Vector3 newScale)
{
	mScale = newScale;

	mDirty = true;

	//Scale changed, update
	updateFromParent();
}