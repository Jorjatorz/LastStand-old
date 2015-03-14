#pragma once

#include <glm\glm.hpp>
#include <glm\gtc\matrix_transform.hpp>
#include <glm\gtc\quaternion.hpp>
#include <glm\gtx\quaternion.hpp>

#include "Quaternion.h"
#include "Matrix4.h"
#include "Vector3.h"

class Math
{
public:
	Math();
	~Math();

	//Trigonometric functions, all in DEGREES
	static float sin(float angle);
	static float cos(float angle);
	static float toDegrees(float radians);
	static float toRadians(float degrees);

	//Vector functions
	static float dotProduct(const Vector3& a, const Vector3& b);
	static Vector3 crossProduct(const Vector3& a, const Vector3& b);
	static Vector3 normalize(const Vector3& a);
	static Vector3 multiply(const Quaternion& quat, const Vector3& vec); //Multiply a vector by a quaternion

	//Matrix
	//Generates a perspective matrix
	static Matrix4 createPerspectiveMatrix(float FOV, float width, float height, float zNear, float zFar);
	static Matrix4 createLookAtMatrix(const Vector3& origin, const Vector3& destination, const Vector3 &up);
	static Matrix4 inverse(const Matrix4& mat);
	static Matrix4 transpose(const Matrix4& mat);
	static Quaternion toQuaternion(const Matrix4& mat);

	//Quaternions
	static Matrix4 toMat4(const Quaternion& quat);
	static Vector3 toEulerAngles(const Quaternion& quat);
	static Quaternion normalize(const Quaternion& quat);
	static Quaternion rotationBetweenVectors(Vector3 start, Vector3 dest);
	static Quaternion slerp(const Quaternion& quat1, const Quaternion& quat2, float amount);
};

