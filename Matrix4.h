#pragma once

#include "Vector3.h"

#include <glm\glm.hpp>
#include <glm\gtc\matrix_transform.hpp>

class Matrix4
{
public:
	//Creates an identity matrix
	Matrix4();
	//Creates a matrix with all 0 except in the diagonal
	Matrix4(float diagonalValue);

	~Matrix4();

	//Operator overloading
	Matrix4& operator=(const Matrix4& other);
	bool operator==(const Matrix4& other) const;

	Matrix4 operator+(const Matrix4& other);
	Matrix4 operator-(const Matrix4& other);
	Matrix4 operator*(const Matrix4& other);
	Matrix4 operator/(const Matrix4& other);

	//Return a matrix that is the inverse of itself
	Matrix4 getInverseMatrix();
	//Return a matrix that is the inverse of the parameter matrix
	static Matrix4 inverse(const Matrix4& mat);
	//Return a matrix that is the transpose of itself
	Matrix4 getTransposeMatrix();
	//Return a matrix that is the transpose of the parameter matrix
	static Matrix4 transpose(const Matrix4& mat);

	//Translates the matrix by a given vector
	void translate(const Vector3& transVec);
	//Rotates the matrix by a given an angle and a vector
	void rotate(float angle, const Vector3& rotVec);
	//Rotates the matrix by a given a degree vector
	void rotate(const Vector3& rotVec);
	//Scales the matrix by a given vector value
	void scale(const Vector3& scaleVec);

private:
	//Real matrix. Use GLM to do matrix calculations
	glm::mat4 mGLMMatrix;

	//Let Quaternion class read the glm matrix
	friend class Quaternion;
};

