#pragma once

#include <iostream>
#include <glm\glm.hpp>
#include <glm\gtc\quaternion.hpp>
#include <glm\gtx\quaternion.hpp>

//Forward declaration
class Matrix4;
class Vector3;

class Quaternion
{
public:
	Quaternion();
	Quaternion(float w, float x, float y, float z);
	Quaternion(float x, float y, float z); //Euler angles to quaternion, in degrees
	Quaternion(const Vector3& euler); //Euler angles to quaternion, in degrees
	Quaternion(float radians, const Vector3& axis);
	~Quaternion();


	//Operator overloading
	friend std::ostream& operator<<(std::ostream& out, Quaternion& quat);

	Quaternion& operator=(const Quaternion& other);
	bool operator==(const Quaternion& other) const;
	bool operator!=(const Quaternion& other) const;

	Quaternion operator+(const Quaternion& other);
	Quaternion operator*(const Quaternion& other);

	Quaternion operator-();

	//Normalize the quaternion
	void normalize();

	float getX()
	{
		return mGLMQuat.x;
	}
	float getY()
	{
		return mGLMQuat.y;
	}
	float getZ()
	{
		return mGLMQuat.z;
	}
	float getW()
	{
		return mGLMQuat.w;
	}

private:
	//GLM quaternion, incharge of all the operations.
	glm::quat mGLMQuat;

	friend class Math;
};

