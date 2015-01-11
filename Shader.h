#pragma once

#include "FEngine.h"

#include <string>

class Shader
{
public:
	Shader(std::string name);
	~Shader(void);

	//shader locations
	typedef enum
	{
		VERTEXPOSITION, //0
		VERTEXNORMALS, //1
		VERTEXTEXCOORD //2
	} shaderLocations;

	void loadShader(std::string filePath);

	GLuint getShaderProgram();

	// Communication with shader
	void UniformTexture(const std::string& uniformName, GLint activeTextureSlot);
	void Uniform(const std::string& uniformName, GLint value);
	void Uniform(const std::string& uniformName, GLfloat value);
	void Uniform(const std::string& uniformName, const Vector3& value);

private:
	//Variables
	//Shader program and shader name
	std::string mName;
	GLuint mProgram;

	//Private functions
	//bind the shader (gl_UsePorgram)
	void bind();
	//unbind the shader
	void unBind();

};
