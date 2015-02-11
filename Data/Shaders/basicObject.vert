#version 430 core

layout (location = 0) in vec3 position;
layout (location = 1) in vec3 normal;
layout (location = 2) in vec2 texCoord;

out vec2 uv;
out vec3 vNormal;

uniform mat4 MVP; //ModelViewPerspective matrix
uniform mat4 NormalM;

void main()
{
	vNormal = (NormalM * vec4(normal, 1.0)).xyz * 0.5 + 0.5; //Compute the normal transformation and 

	uv = texCoord;		
	gl_Position =  MVP * vec4(position, 1.0);
}