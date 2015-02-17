#include "Quaternion.h"

#include "Matrix4.h"

Quaternion::Quaternion()
	:mGLMQuat()
{
}

Quaternion::Quaternion(Matrix4 mat)
	: mGLMQuat(mat.mGLMMatrix)
{

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

Matrix4 Quaternion::toMat4()
{
	Matrix4 mat;
	mat.mGLMMatrix = glm::toMat4(mGLMQuat);

	return mat;
}

Quaternion Quaternion::operator-()
{
	Quaternion newQuat;

	newQuat.mGLMQuat = -mGLMQuat;

	return newQuat;
}