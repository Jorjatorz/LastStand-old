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

	//Load the shader, false if an error ocurred
	bool loadShader(std::string filePath);

	//Return the gl shader program
	GLuint getShaderProgram();
	//bind the shader (gl_UsePorgram)
	void bind();
	//unbind the shader
	static void unBind();

	// Communication with shader
	void uniformTexture(const std::string& uniformName, GLint activeTextureSlot);
	void uniform(const std::string& uniformName, GLint value);
	void uniform(const std::string& uniformName, GLfloat value);
	void uniform(const std::string& uniformName, const Vector3& value);
	void uniformMatrix(const std::string & uniformName, const Matrix4& value);

private:
	//Variables
	//Shader program and shader name
	std::string mName;
	GLuint mProgram;

};
