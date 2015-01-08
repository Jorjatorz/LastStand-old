#pragma once

#include <glm\glm.hpp>

//Warp class for glm vector
class Vector3
{
public:
	Vector3();
	Vector3(const float& xyz);
	Vector3(const float& x, const float& y, const float& z);
	~Vector3();

	//Operator overloading
	Vector3& operator=(const Vector3& other);
	bool operator==(const Vector3& other);

	Vector3 operator+(const Vector3& other);
	Vector3 operator-(const Vector3& other);
	Vector3 operator*(const Vector3& other);
	Vector3 operator/(const Vector3& other);

	Vector3 operator+(const float& n);
	Vector3 operator-(const float& n);
	Vector3 operator*(const float& n);
	Vector3 operator/(const float& n);
	

	//Vector components
	float x, y, z;

private:
	//Hidden glm vector (which is the real vector)
	glm::vec3 mGLMVector;
	//Function to copy the glm vector components to the x,y,z of this class
	inline void copyFromGLMVector();
};

