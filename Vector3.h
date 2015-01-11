#pragma once

#include <glm\glm.hpp>
#include <glm\gtc\type_ptr.hpp>

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

	//Return the constant address of the first element of the vector
	const float* getValuePtr() const;

	//Vector components (same value different name)
	union{ float x, r, s;};
	union{ float y, g, t; };
	union{ float z, b, p; };

};

