#pragma once

#include "FEngine.h"

#include "MovableObject.h"

class Camera: public MovableObject
{
public:
	Camera(std::string name);
	~Camera();

	virtual void rendersMovableObject(const Matrix4& PVMatrix);

	void processViewMatrix(); //If is dirty it recalculates the viewMatrix;
	//Returns the viewmatrix of the camera
	Matrix4 getViewMatrix()
	{
		return mViewMatrix;
	}

	//Setters
	void setPosition(const Vector3& newPos);
	void setOrientation(const Quaternion& newOrient);
	void translate(const Vector3& trans);
	void rotate(Vector3 axis, float angle);
	void roll(float amount); //Rotate on X axis, amount in degrees
	void yaw(float amount); //Rotate on Y axis, amount in degrees
	void pitch(float amount); //Rotate on Z axis, amount in degrees

	//Getters
	Vector3 getPostion()
	{
		return mPosition;
	}
	Vector3 getDerivedPosition()
	{
		return mLastParentPosition + mPosition;
	}
	Quaternion getOrientation()
	{
		return mOrientation;
	}
	Quaternion  getDerivedOrientation()
	{
		return mLastParentOrientation + mOrientation;
	}

private:
	Vector3 mPosition, mLastParentPosition;
	Quaternion mOrientation, mLastParentOrientation;
	Matrix4 mViewMatrix;

	bool mDirty; //True if the viewMatrix needs update

	//Recalculates the viewMatrix
	void recalculateViewMatrix();
};
