#include "Camera.h"

#include "Root.h"
#include "SceneNode.h"

Camera::Camera(std::string name)
	:MovableObject(name, MovableObject::RENDERABLE),
	mDirty(true),
	mPosition(0.0),
	mOrientation()
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

			mDirty = false;
		}
	}
	else
	{
		//If we have a change modify the view
		if (mDirty)
		{
			recalculateViewMatrix();

			mDirty = false;
		}
	}
}

void Camera::recalculateViewMatrix()
{
	mViewMatrix = Matrix4();

	Vector3 finalPosition = mLastParentPosition + mPosition;
	Quaternion finalOrientation = mLastParentOrientation * mOrientation;

	std::cout << finalOrientation << std::endl;

	Vector3 eulerA = Math::multiply(finalOrientation, Vector3(0.0, 0.0, -1.0));

	mViewMatrix = Math::createLookAtMatrix(finalPosition, finalPosition + eulerA, Vector3(0.0, 1.0, 0.0));
}

void Camera::setPosition(const Vector3& newPos)
{
	mPosition = newPos;
	mDirty = true;
}

void Camera::setOrientation(const Quaternion& newOrientation)
{
	mOrientation = newOrientation;
	mDirty = true;
}

void Camera::translate(const Vector3& trans)
{
	mPosition += trans * Root::getSingleton()->getLastFrameDelayInSeconds();
	mDirty = true;
}

void Camera::rotate(float angle, const Vector3& axis)
{
	rotate(Quaternion(Math::toRadians(angle * Root::getSingleton()->getLastFrameDelayInSeconds()), axis));
}

void Camera::rotate(const Quaternion& quat)
{
	Quaternion dest = quat;
	dest.normalize();

	mOrientation = dest * mOrientation;

	mDirty = true;
}

void Camera::pitch(float angle)
{
	//Rotate around the local X axis
	Vector3 axis = Math::multiply(mOrientation, Vector3(1.0, 0.0, 0.0));

	rotate(angle, axis);
}

void Camera::yaw(float angle)
{
	//Rotate around the local Y axis
	Vector3 axis = Math::multiply(mOrientation, Vector3(0.0, 1.0, 0.0));

	rotate(angle, axis);
}

void Camera::roll(float angle)
{
	//Rotate around the local Z axis
	Vector3 axis = Math::multiply(mOrientation, Vector3(0.0, 0.0, 1.0));

	rotate(angle, axis);
}