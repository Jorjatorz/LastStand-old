#include "Vector3.h"


Vector3::Vector3()
	:x(0.0), r(0.0),
	y(0.0), g(0.0),
	z(0.0), b(0.0),
	mGLMVector(0.0)
{
}

Vector3::Vector3(const float& xyz)
	:x(xyz), r(xyz),
	y(xyz), g(xyz),
	z(xyz), b(xyz),
	mGLMVector(xyz)
{

}
Vector3::Vector3(const float& x, const float& y, const float& z)
	:mGLMVector(x, y, z)
{
	copyFromGLMVector();
}


Vector3::~Vector3()
{
}

void Vector3::copyFromGLMVector()
{
	//Set the public class components equal to the glm vector components
	x = r = mGLMVector.x;
	y = g = mGLMVector.y;
	z = b = mGLMVector.z;
}


Vector3& Vector3::operator=(const Vector3& other)
{
	mGLMVector = other.mGLMVector;
	copyFromGLMVector();

	return *this;
}

bool Vector3::operator == (const Vector3& other)
{
	return mGLMVector == other.mGLMVector;
}

Vector3 Vector3::operator+(const Vector3& other)
{
	Vector3 result;
	result.mGLMVector = mGLMVector + other.mGLMVector;
	result.copyFromGLMVector();
	return result;
}
Vector3 Vector3::operator-(const Vector3& other)
{
	Vector3 result;
	result.mGLMVector = mGLMVector - other.mGLMVector;
	result.copyFromGLMVector();
	return result;
}
Vector3 Vector3::operator*(const Vector3& other)
{
	Vector3 result;
	result.mGLMVector = mGLMVector * other.mGLMVector;
	result.copyFromGLMVector();
	return result;
}
Vector3 Vector3::operator/(const Vector3& other)
{
	Vector3 result;
	result.mGLMVector = mGLMVector / other.mGLMVector;
	result.copyFromGLMVector();
	return result;
}

Vector3 Vector3::operator+(const float& n)
{
	Vector3 result;
	result.mGLMVector = mGLMVector + n;
	result.copyFromGLMVector();
	return result;
}
Vector3 Vector3::operator-(const float& n)
{
	Vector3 result;
	result.mGLMVector = mGLMVector - n;
	result.copyFromGLMVector();
	return result;
}
Vector3 Vector3::operator*(const float& n)
{
	Vector3 result;
	result.mGLMVector = mGLMVector * n;
	result.copyFromGLMVector();
	return result;
}
Vector3 Vector3::operator/(const float& n)
{
	Vector3 result;
	result.mGLMVector = mGLMVector / n;
	result.copyFromGLMVector();
	return result;
}