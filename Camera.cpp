#include "Camera.h"

#include "Root.h"
#include "SceneNode.h"

Camera::Camera(std::string name)
	:MovableObject(name, MovableObject::RENDERABLE),
	mDirty(true),
	mPosition(Vector3(0.0)),
	mLastParentPosition(Vector3(0.0)),
	mOrientation(Quaternion()),
	mLastParentOrientation(Quaternion())
{
}


Camera::~Camera()
{
}

void Camera::rendersMovableObject(const Matrix4& PVMatrix)
{
	//NULL
}

void Camera::processViewMatrix()
{
	if (mParentSceneNode != NULL)
	{
		//If we have a change modify the view
		if (mDirty || mParentSceneNode->getDerivedPosition() != mLastParentPosition || mParentSceneNode->getDerivedOrientation() != mLastParentOrientation)
		{
			mLastParentPosition = mParentSceneNode->getDerivedPosition();
			mLastParentOrientation = mParentSceneNode->getDerivedOrientation();

			recalculateViewMatrix();
		}
	}
	else
	{
		//If we have a change modify the view
		if (mDirty)
		{
			recalculateViewMatrix();
		}
	}
}

void Camera::recalculateViewMatrix()
{
	mViewMatrix = Matrix4();

	//Calculate new view matrix, the viewmatrix translates and rotates everything opposite to the camera and orientation position
	mViewMatrix.translate(-(mLastParentPosition + mPosition));
	mViewMatrix = mViewMatrix * (-(mLastParentOrientation * mOrientation)).toMat4();
}

void Camera::setPosition(const Vector3& newPos)
{
	mPosition = newPos;
	mDirty = true;
}
void Camera::setOrientation(const Quaternion& newOrient)
{
	mOrientation = newOrient;
	mDirty = true;
}

void Camera::translate(const Vector3& trans)
{
	mPosition += trans * Root::getSingleton()->getLastFrameDelayInSeconds();
	mDirty = true;
}

void Camera::rotate(Vector3 axis, float angle)
{
	Matrix4 rotationM;
	if (axis != Vector3(0.0)) //Just in case
	{
		rotationM.rotate(angle * Root::getSingleton()->getLastFrameDelayInSeconds(), axis);
	}

	//Create a quaternion from the matrix
	mOrientation = mOrientation * Quaternion(rotationM);

	mDirty = true;
}

void Camera::roll(float amount)
{
	rotate(Vector3(0.0, 1.0, 0.0), amount);
}

void Camera::yaw(float amount)
{
	rotate(Vector3(0.0, 1.0, 0.0), amount);
}

void Camera::pitch(float amount)
{
	rotate(Vector3(0.0, 1.0, 0.0), amount);
}
