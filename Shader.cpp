#include "Shader.h"

Shader::Shader(std::string name)
	:mProgram(0),
	mName(name)
{
}


Shader::~Shader(void)
{
	//delete the program
	glDeleteProgram(mProgram);
}

void Shader::loadShader(std::string filePath)
{
	std::ifstream file;
	std::stringstream strStreamBuffer; //string stream buffer

	//vertex-------------------------------------

	//load
	file.open(filePath + ".vert");

	std::string vertexShaderStr; //string

	if (!file.is_open())
	{
		FE_LOG(FE_LOG::ERR, "Error loading VERTEX shader: " + filePath);
	}
	else
	{
		strStreamBuffer << file.rdbuf(); //read the file
		vertexShaderStr = strStreamBuffer.str(); //copy to a string

		file.close();
	}


	//create the vertex shader source
	const GLchar* vertexShaderSource = vertexShaderStr.c_str();

	//Create and compile the shader
	GLuint vertexShader;
	vertexShader = glCreateShader(GL_VERTEX_SHADER);
	glShaderSource(vertexShader, 1, &vertexShaderSource, NULL);
	glCompileShader(vertexShader);

	// Check vertex shader
	GLint status;
	glGetShaderiv(vertexShader, GL_COMPILE_STATUS, &status);
	char buffer[512];
	glGetShaderInfoLog(vertexShader, 512, NULL, buffer);


	if (status == 0)
	{
		FE_LOG(FE_LOG::WARNING, buffer);
	}

	//fragment------------------------

	//load
	file.open(filePath + ".frag");

	std::string fragmentShaderStr; //strings

	if (!file.is_open())
	{
		FE_LOG(FE_LOG::ERR, "Error loading FRAGMENT shader: " + filePath);
	}
	else
	{
		//reset stream buffer
		strStreamBuffer.str("");
		strStreamBuffer.clear();

		strStreamBuffer << file.rdbuf();
		fragmentShaderStr = strStreamBuffer.str();

		file.close();
	}

	//create
	const GLchar* fragmentShaderSource = fragmentShaderStr.c_str();

	GLuint fragmentShader;
	fragmentShader = glCreateShader(GL_FRAGMENT_SHADER);
	glShaderSource(fragmentShader, 1, &fragmentShaderSource, NULL);
	glCompileShader(fragmentShader);

	// Check fragment shader
	glGetShaderiv(fragmentShader, GL_COMPILE_STATUS, &status);
	glGetShaderInfoLog(fragmentShader, 512, NULL, buffer);

	if (status == 0)
	{
		FE_LOG(FE_LOG::WARNING, buffer);
	}


	// Link the vertex and fragment shader into a shader program--------------------
	GLuint program = glCreateProgram();
	glAttachShader(program, vertexShader);
	glAttachShader(program, fragmentShader);

	//Framgent shader outputs
	glBindFragDataLocation(program, 0, "outColor"); //color to the buffer number 0
	glBindFragDataLocation(program, 1, "outPosition"); //vertex position to the buffer number 1
	glBindFragDataLocation(program, 2, "outNormals"); //normal to the buffer number 2

	glLinkProgram(program);

	//we finished so delete the sahder
	glDeleteShader(fragmentShader);
	glDeleteShader(vertexShader);

	//save the program
	mProgram = program;
}

GLuint Shader::getShaderProgram()
{
	return mProgram;
}

void Shader::bind()
{
	glUseProgram(mProgram); //binds the shader program
}
void Shader::unBind()
{
	glUseProgram(0); //unbids the shader program
}

// sent texture value
void Shader::UniformTexture(const std::string& uniformName, GLint activeTextureSlot)
{
	//glActiveTexture(GL_TEXTURE0+slot);
	GLuint id = glGetUniformLocation(mProgram, uniformName.c_str());
	if (id == -1)
		FE_LOG(FE_LOG::WARNING, mName + " Couldn't get uniform location of " + uniformName);

	glUniform1i(id, activeTextureSlot);
}

// sent int value
void Shader::Uniform(const std::string& uniformName, GLint value)
{
	GLuint id = glGetUniformLocation(mProgram, uniformName.c_str());
	if (id == -1)
		FE_LOG(FE_LOG::WARNING, mName + " Couldn't get uniform location of " + uniformName);
	glUniform1iARB(id, value);
}

// sent float value
void Shader::Uniform(const std::string& uniformName, GLfloat value)
{
	GLuint id = glGetUniformLocation(mProgram, uniformName.c_str());
	if (id == -1)
		FE_LOG(FE_LOG::WARNING, mName + " Couldn't get uniform location of " + uniformName);
	glUniform1fARB(id, value);
}

void Shader::Uniform(const std::string& uniformName, const Vector3& value)
{
	GLuint id = glGetUniformLocation(mProgram, uniformName.c_str());
	if (id == -1)
		FE_LOG(FE_LOG::WARNING, mName + " Couldn't get uniform location of " + uniformName);
	glUniform3fvARB(id, 1, value.getValuePtr());
}