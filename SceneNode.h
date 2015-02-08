#pragma once

#include "FEngine.h"


//Class that holds the transformation of MovableObjects. Similar strcuture to a tree

class SceneNode
{
public:
	SceneNode(std::string sceneNodeName, SceneManager* manager, SceneNode* nodeParent = NULL);
	~SceneNode(void);


	//sets the new parent to the sceneNode
	void setParentSceneNode(SceneNode* newParent);
	//adds a new child to the sceneNode given a name
	SceneNode* createChildSceneNode(std::string name);
	//adds a new child to the sceneNode given a name and a initial position
	SceneNode* createChildSceneNode(std::string name, Vector3 initialPosition);
	//adds a new child to the sceneNode given a name and a scenenode
	SceneNode* createChildSceneNode(std::string name, SceneNode* newChild);
	//deletes a children given its name
	void deleteChildrenNode(std::string childName);
	//deletes a children given its pointer
	void deleteChildrenNode(SceneNode* child);
	//deletes all the childs
	void deleteAllChilds();
	//Return the child map
	const std::unordered_map<std::string, SceneNode*>& getChildNodesMap() const
	{
		return mChildNodesMap;
	}

	//attach a movableobjecto to the scenenode
	void attachObject(MovableObject* mNewObject);
	//deatach an object by name
	void detachObject(std::string objName);
	//deatach an object
	void detachObject(MovableObject* movableObject);
	//Deatach all the attached movable objects
	void detachAllObjects();
	//Return the movableobject map
	const std::unordered_map<std::string, MovableObject*>& getMovablesObjectsMap() const
	{
		return mMovableObjectsMap;
	}

	//transformations functions
	void translate(Vector3 trans);
	void rotate(Vector3 axis, float angle);
	void scale(Vector3 axis);
	void setPosition(Vector3 newPos);
	void setOrientation(Quaternion newOrientation);
	void setScale(Vector3 newScale);
	void lookAt(Vector3 lookAtPoint, Vector3 objectFacing = Vector3(0.0, 0.0, 1.0)); //Rotate the objectec so it face the new point, objectFacing is the object direction that is facing at the origin (i.e the initial orientation of the mesh)

	//returns
	Matrix4 getSceneNodeMatrix()
	{
		return mSceneNodeMatrix;
	}

	Vector3 getPosition()
	{
		return mPosition;
	}
	Quaternion getOrientation()
	{
		return mOrientation;
	}
	Vector3 getScale()
	{
		return mScale;
	}
	Vector3 getDerivedPosition()
	{
		processDerivedPosition();
		return mDerivedPosition;
	}
	Quaternion getDerivedOrientation()
	{
		processDerivedOrientation();
		return mDerivedOrientation;
	}
	Vector3 getDerivedScale()
	{
		processDerivedScale();
		return mDerivedScale;
	}

	std::string getName()
	{
		return mName;
	}
private:
	//scenenode matrix which represents the final position, orientation and scale of the node
	Matrix4 mSceneNodeMatrix;
	//scenenode position, orientation and scale
	Vector3 mPosition, mScale;
	Quaternion mOrientation;
	//derived scenenode position, orientation and scale (Derived = ParentTrans + nodeTrans)
	Vector3 mDerivedPosition, mDerivedScale;
	Quaternion  mDerivedOrientation;

	//true if the node has changed, so we need to update it
	bool mDirty;

	//Parent Scenenode (NULL if it's the root)
	SceneNode* mParent;

	//Scenemanager creator of the node
	SceneManager* creator;

	//Map containing all the movableobjects attached to this scenenode
	std::unordered_map<std::string, MovableObject*> mMovableObjectsMap;

	//Map containing all the scenenodes attached to this scenenode (called child nodes)
	std::unordered_map<std::string, SceneNode*> mChildNodesMap;

	//scenenode name
	std::string mName;

	//Private Functions
	//Gets the position from the parent and with his position compute the final position
	void processDerivedPosition();
	//Gets the orientation from the parent and with his orientation compute the final orientation
	void processDerivedOrientation();
	//Gets the scale from the parent and with his scale compute the final scale
	void processDerivedScale();

	//Process all the derived transforms and updates the scenenode matrix
	void updateFromParent();
	//Go through all his childrens updating all the transforms of them
	void updateChildrens();
};

