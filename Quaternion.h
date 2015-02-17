#pragma once

#include <glm\glm.hpp>
#include <glm\gtc\quaternion.hpp>
#include <glm\gtx\quaternion.hpp>

//Forward declaration
class Matrix4;

class Quaternion
{
public:
	Quaternion();
	Quaternion(Matrix4 mat);
	~Quaternion();


	//Operator overloading
	Quaternion& operator=(const Quaternion& other);
	bool operator==(const Quaternion& other) const;
	bool operator!=(const Quaternion& other) const;

	Quaternion operator+(const Quaternion& other);
	Quaternion operator*(const Quaternion& other);

	Quaternion operator-();

	//Transform the quaternion into a matrix
	Matrix4 toMat4();

private:
	//GLM quaternion, incharge of all the operations.
	glm::quat mGLMQuat;
};

