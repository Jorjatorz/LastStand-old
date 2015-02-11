#version 430 core

layout (location = 0) out vec4 outColor; 
layout (location = 1) out vec4 outNormals; 

in vec3 vNormal;

void main()
{
	outNormals = vec4(vNormal, 1.0);

	outColor = vec4(1.0, 0.0, 0.0, 1.0);
}