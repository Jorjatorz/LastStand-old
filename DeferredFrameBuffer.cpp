#include "DeferredFrameBuffer.h"

#include "ResourceManager.h"
#include "Shader.h"

DeferredFrameBuffer::DeferredFrameBuffer(std::string name, int width, int height)
	:FrameBuffer(name, width, height)
{
	//Create the textures
	//Color Texture. Attachment 0
	addTexture("DeferredFrameBufferText_Color", GL_RGBA8);
	//Normal Texture. Attachment 1
	addTexture("DeferredFrameBufferText_Normal", GL_RGBA8);
	//Light Texture. Attachment 2
	addTexture("DeferredFrameBufferText_Light", GL_RGBA8);

	//Create the Depth texture
	glGenTextures(1, &depthTextureId);
	glBindTexture(GL_TEXTURE_2D, depthTextureId);

	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);

	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);


	glTexImage2D(GL_TEXTURE_2D, 0, GL_DEPTH_COMPONENT24, mWidth, mHeight, 0, GL_DEPTH_COMPONENT, GL_FLOAT, 0);

	glBindFramebuffer(GL_FRAMEBUFFER, mFrameBufferId);
	glFramebufferTexture2D(GL_FRAMEBUFFER, GL_DEPTH_ATTACHMENT, GL_TEXTURE_2D, depthTextureId, 0);

	glBindTexture(GL_TEXTURE_2D, 0);

	//Create ScreenQuad buffers
	glGenVertexArrays(1, &screenQuadVAO);
	glBindVertexArray(screenQuadVAO);

	glGenBuffers(1, &screenQuadVBO);
	glBindBuffer(GL_ARRAY_BUFFER, screenQuadVBO);

	glVertexAttribPointer(Shader::VERTEXPOSITION, 2, GL_FLOAT, GL_FALSE, 4 * sizeof(GLfloat), 0);
	glVertexAttribPointer(Shader::VERTEXTEXCOORD, 2, GL_FLOAT, GL_FALSE, 4 * sizeof(GLfloat), (void*)(2 * sizeof(GLfloat)));
	glEnableVertexAttribArray(Shader::VERTEXPOSITION);
	glEnableVertexAttribArray(Shader::VERTEXTEXCOORD);
	glBindBuffer(GL_ARRAY_BUFFER, 0);
	glBindVertexArray(0);

	//Load shaders
	ResourceManager::getSingleton()->loadShaderIntoMemoryFromFile("DeferredShading_Combination");
}


DeferredFrameBuffer::~DeferredFrameBuffer()
{
	glDeleteTextures(1, &depthTextureId);
}

void DeferredFrameBuffer::bindForGeometryPass()
{
	glBindFramebuffer(GL_FRAMEBUFFER, mFrameBufferId);
	GLuint geometryAttachments[] = { GL_COLOR_ATTACHMENT0, GL_COLOR_ATTACHMENT1};

	//Draw to buffers
	glDrawBuffers(2, geometryAttachments);
}

void DeferredFrameBuffer::bindForLightPass()
{
	glBindFramebuffer(GL_FRAMEBUFFER, mFrameBufferId);
	GLuint lightAttachments[] = { GL_COLOR_ATTACHMENT2};

	//Draw to buffer
	glDrawBuffers(1, lightAttachments);
}

void DeferredFrameBuffer::drawToScreenQuad(float startX, float startY, float endX, float endY)
{
	//Unbind any active framebuffer
	unBind();

	//Vertex and UV data
	const GLfloat vertex_positions[] =
	{
		startX, startY, 0.0f, 1.0f,
		endX, startY, 1.0f, 1.0f,
		endX, endY, 1.0f, 0.0f,

		endX, endY, 1.0f, 0.0f,
		startX, endY, 0.0f, 0.0f,
		startX, startY, 0.0f, 1.0f
	};

	glBindBuffer(GL_ARRAY_BUFFER, screenQuadVBO);
	glBufferData(GL_ARRAY_BUFFER, sizeof(vertex_positions), vertex_positions, GL_STATIC_DRAW);
	glBindBuffer(GL_ARRAY_BUFFER, 0);

	//Bind shader


	glDisable(GL_DEPTH_TEST);
	glBindVertexArray(screenQuadVAO);

	ResourceManager::getSingleton()->getShaderInMemory("DeferredShading_Combination")->bind();

	glDrawArrays(GL_TRIANGLES, 0, 6);

	glBindVertexArray(0);
	glEnable(GL_DEPTH_TEST);

	Shader::unBind();
}