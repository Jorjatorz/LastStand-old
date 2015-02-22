#include "Camera.h"

#include "Root.h"
#include "SceneNode.h"

Camera::Camera(std::string name)
	:MovableObject(name, MovableObject::RENDERABLE),
	mDirty(true),
	mPosition(0.0),
	mLastParentPosition(0.0),
	mOrientation(),
	mLastParentOrientation()
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
	Vector3 finalOrientation = Math::toEulerAngles(mOrientation * mLastParentOrientation);
	std::cout << finalOrientation.x << " " << finalOrientation.y << " " << finalOrientation.z << std::endl;

	//mViewMatrix = Math::createLookAtMatrix(finalPosition, finalPosition + finalOrientation, Vector3(0.0, 1.0, 0.0));

	/*//Calculate new view matrix, the viewmatrix translates and rotates everything opposite to the camera and orientation position
	mViewMatrix.translate(-(mLastParentPosition + mPosition));
	mViewMatrix = mViewMatrix * Math::toMat4(-(mLastParentOrientation * mOrientation));*/
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
	if (axis != Vector3(0.0) && (angle != 0)) //Just in case
	{
		mOrientation = Quaternion(angle * Root::getSingleton()->getLastFrameDelayInSeconds(), axis) * mOrientation;

		mOrientation = Math::normalize(mOrientation);

		mDirty = true;
	}
}

void Camera::roll(float amount)
{
	rotate(Vector3(1.0, 0.0, 0.0), amount);
}

void Camera::yaw(float amount)
{
	rotate(Vector3(0.0, 1.0, 0.0), amount);
}

void Camera::pitch(float amount)
{
	rotate(Vector3(0.0, 0.0, 1.0), amount);
}
