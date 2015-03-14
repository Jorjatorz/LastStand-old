#include "Math.h"


Math::Math()
{
}


Math::~Math()
{
}

float  Math::sin(float angle)
{
	return glm::sin(glm::degrees(angle));
}

float  Math::cos(float angle)
{
	return glm::cos(glm::degrees(angle));
}

float Math::toDegrees(float radians)
{
	return glm::degrees(radians);
}

float Math::toRadians(float degrees)
{
	return glm::radians(degrees);
}

float  Math::dotProduct(const Vector3& a, const Vector3& b)
{
	glm::vec3 op1 = glm::vec3(a.x, a.y, a.z);
	glm::vec3 op2 = glm::vec3(b.x, b.y, b.z);

	return glm::dot(op1, op2);
}

Vector3  Math::crossProduct(const Vector3& a, const Vector3& b)
{
	glm::vec3 op1 = glm::vec3(a.x, a.y, a.z);
	glm::vec3 op2 = glm::vec3(b.x, b.y, b.z);

	glm::vec3 result = glm::cross(op1, op2);

	return Vector3(result.x, result.y, result.z);
}

Vector3 Math::normalize(const Vector3& a)
{
	if (a != 0.0)
	{
		Vector3 toRet;

		glm::vec3 aux = glm::normalize(glm::vec3(a.x, a.y, a.z));

		toRet.x = aux.x;
		toRet.y = aux.y;
		toRet.z = aux.z;

		return toRet;
	}
	else
	{
		return a;
	}
}

Vector3 Math::multiply(const Quaternion& quat, const Vector3& vec)
{
	glm::vec3 aux(vec.x, vec.y, vec.z);

	glm::vec3 result = quat.mGLMQuat * aux;

	return Vector3(result.x, result.y, result.z);
}

Matrix4 Math::createPerspectiveMatrix(float FOV, float width, float height, float zNear, float zFar)
{
	Matrix4 newMat;
	newMat.mGLMMatrix = glm::perspective(FOV, width / height, zNear, zFar);

	return newMat;
}

Matrix4 Math::createLookAtMatrix(const Vector3& origin, const Vector3& destination, const Vector3 &up)
{
	Matrix4 toRet;

	glm::vec3 or, dest, u;
	or = glm::vec3(origin.x, origin.y, origin.z);
	dest = glm::vec3(destination.x, destination.y, destination.z);
	u = glm::vec3(up.x, up.y, up.z);

	toRet.mGLMMatrix = glm::lookAt(or, dest, u);

	return toRet;
}

Matrix4 Math::inverse(const Matrix4& mat)
{
	Matrix4 newM;
	newM.mGLMMatrix = glm::inverse(mat.mGLMMatrix);
	return newM;
}

Matrix4 Math::transpose(const Matrix4& mat)
{
	Matrix4 newM;
	newM.mGLMMatrix = glm::transpose(mat.mGLMMatrix);
	return newM;
}

Quaternion Math::toQuaternion(const Matrix4& mat)
{
	Quaternion quat;
	
	quat.mGLMQuat = glm::quat(mat.mGLMMatrix);

	return quat;
}

Matrix4 Math::toMat4(const Quaternion& quat)
{
	Matrix4 mat;
	mat.mGLMMatrix = glm::toMat4(quat.mGLMQuat);

	return mat;
}

Vector3 Math::toEulerAngles(const Quaternion& quat)
{
	Vector3 toRet;
	glm::vec3 euler = glm::eulerAngles(quat.mGLMQuat);

	toRet.x = euler.x;
	toRet.y = euler.y;
	toRet.z = euler.z;

	return toRet;
}

Quaternion Math::normalize(const Quaternion& quat)
{
	Quaternion toRet;

	toRet.mGLMQuat = glm::normalize(quat.mGLMQuat);

	return toRet;
}

Quaternion Math::rotationBetweenVectors(Vector3 start, Vector3 dest)
{

	start = Math::normalize(start);
	dest = Math::normalize(dest);

	float cosTheta = Math::dotProduct(start, dest);
	Vector3 rotationAxis;

	if (cosTheta < -1 + 0.001f){
		// special case when vectors in opposite directions:
		// there is no "ideal" rotation axis
		// So guess one; any will do as long as it's perpendicular to start
		rotationAxis = Math::crossProduct(Vector3(0.0f, 0.0f, 1.0f), start);
		/*if (glm::length2(rotationAxis) < 0.01) // bad luck, they were parallel, try again!
			rotationAxis = Math::crossProduct(Vector3(1.0f, 0.0f, 0.0f), start);*/

		rotationAxis = normalize(rotationAxis);
		return Quaternion(180.0f, rotationAxis);
	}

	rotationAxis = Math::crossProduct(start, dest);

	float s = sqrt((1 + cosTheta) * 2);
	float invs = 1 / s;

	return Quaternion(
		s * 0.5f,
		rotationAxis.x * invs,
		rotationAxis.y * invs,
		rotationAxis.z * invs
		);

}
Quaternion Math::slerp(const Quaternion& quat1, const Quaternion& quat2, float amount)
{
	Quaternion newQuat;

	newQuat.mGLMQuat = glm::slerp(quat1.mGLMQuat, quat2.mGLMQuat, amount);

	return newQuat;
}
