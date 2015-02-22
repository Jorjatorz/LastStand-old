#include "Quaternion.h"

#include "Matrix4.h"
#include "Vector3.h"

Quaternion::Quaternion()
	:mGLMQuat()
{
}

Quaternion::Quaternion(float w, float x, float y, float z)
	: mGLMQuat(w, x, y, z)
{
}

Quaternion::Quaternion(float x, float y, float z)
{
	glm::vec3 eulerA(x, y, z);
	mGLMQuat = glm::quat(glm::radians(eulerA));
}

Quaternion::Quaternion(const Vector3& euler)
{
	glm::vec3 eulerA(euler.x, euler.y, euler.z);
	mGLMQuat = glm::quat(glm::radians(eulerA));
}

Quaternion::Quaternion(float degrees, const Vector3& axis)
{
	glm::vec3 eulerA(axis.x, axis.y, axis.z);

	mGLMQuat = glm::angleAxis(degrees, eulerA);
}

Quaternion::~Quaternion()
{
}

Quaternion& Quaternion::operator=(const Quaternion& other)
{
	mGLMQuat = other.mGLMQuat;

	return *this;
}

bool Quaternion::operator==(const Quaternion& other) const
{
	return mGLMQuat == other.mGLMQuat;
}

bool Quaternion::operator!=(const Quaternion& other) const
{
	return mGLMQuat != other.mGLMQuat;
}

Quaternion Quaternion::operator+(const Quaternion& other)
{
	Quaternion quat;
	quat.mGLMQuat = mGLMQuat + other.mGLMQuat;
	return quat;
}

Quaternion Quaternion::operator*(const Quaternion& other)
{
	Quaternion quat;
	quat.mGLMQuat = mGLMQuat * other.mGLMQuat;
	return quat;
}

Quaternion Quaternion::operator-()
{
	Quaternion newQuat;

	newQuat.mGLMQuat = -mGLMQuat;

	return newQuat;
}