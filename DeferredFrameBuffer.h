#pragma once

#include "FEngine.h"
#include "FrameBuffer.h"

//FrameBuffer that stores  Color and normal textures and depth texture

class DeferredFrameBuffer: public FrameBuffer
{
public:
	DeferredFrameBuffer(std::string name, int width, int height);
	~DeferredFrameBuffer();

	//Binds the textures that needs to be modified in the geometry pass (special call of the inherited function bindTexturesForDrawing)
	void bindForGeometryPass();
	//Binds the textures that need to be modified in the light pass
	void bindForLightPass();
	//Rendenders a Quad (with desired dimensions) to the screen and writes there the result of the deferred pass
	void drawToScreenQuad(float startX, float startY, float endX, float endY);

private:
	//Depth texture id
	GLuint depthTextureId;
	//ScreenQuad variables
	GLuint screenQuadVAO, screenQuadVBO;
};

