#include "Matrix4.h"

#include "Vector3.h"

Matrix4::Matrix4()
	:mGLMMatrix(1.0)
{
}

Matrix4::Matrix4(float diagonalValue)
	: mGLMMatrix(diagonalValue)
{

}


Matrix4::~Matrix4()
{
}

Matrix4& Matrix4::operator=(const Matrix4& other)
{
	mGLMMatrix = other.mGLMMatrix;

	return *this;
}

bool Matrix4::operator==(const Matrix4& other) const
{
	return mGLMMatrix == other.mGLMMatrix;
}

Matrix4 Matrix4::operator+(const Matrix4& other)
{
	Matrix4 newM;
	newM.mGLMMatrix = mGLMMatrix + other.mGLMMatrix;
	return newM;
}

Matrix4 Matrix4::operator-(const Matrix4& other)
{
	Matrix4 newM;
	newM.mGLMMatrix = mGLMMatrix - other.mGLMMatrix;
	return newM;
}

Matrix4 Matrix4::operator*(const Matrix4& other)
{
	Matrix4 newM;
	newM.mGLMMatrix = mGLMMatrix * other.mGLMMatrix;
	return newM;
}

const Matrix4 Matrix4::operator*(const Matrix4& other) const
{
	Matrix4 newM;
	newM.mGLMMatrix = mGLMMatrix * other.mGLMMatrix;
	return newM;
}

Matrix4 Matrix4::operator/(const Matrix4& other)
{
	Matrix4 newM;
	newM.mGLMMatrix = mGLMMatrix / other.mGLMMatrix;
	return newM;
}

Matrix4 Matrix4::getInverseMatrix()
{
	Matrix4 newM;
	newM.mGLMMatrix = glm::inverse(mGLMMatrix);
	return newM;
}

Matrix4 Matrix4::getTransposeMatrix()
{
	Matrix4 newM;
	newM.mGLMMatrix = glm::transpose(mGLMMatrix);
	return newM;
}



void Matrix4::translate(const Vector3& transVec)
{
	mGLMMatrix = glm::translate(mGLMMatrix, glm::vec3(transVec.x, transVec.y, transVec.z));
}

void Matrix4::rotate(float angle, const Vector3& rotVec)
{
	mGLMMatrix = glm::rotate(mGLMMatrix, angle, glm::vec3(rotVec.x, rotVec.y, rotVec.z));
}

void Matrix4::rotate(const Vector3& rotVec)
{
	mGLMMatrix = glm::rotate(mGLMMatrix, (float)1.0, glm::vec3(rotVec.x, rotVec.y, rotVec.z));
}

void Matrix4::scale(const Vector3& scaleVec)
{
	mGLMMatrix = glm::scale(mGLMMatrix, glm::vec3(scaleVec.x, scaleVec.y, scaleVec.z));
}

const float* Matrix4::getValuePtr() const
{
	return &mGLMMatrix[0].x;
}